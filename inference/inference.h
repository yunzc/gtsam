/**
 * @file    inference.h
 * @brief   Contains *generic* inference algorithms that convert between templated
 * graphical models, i.e., factor graphs, Bayes nets, and Bayes trees
 * @author  Frank Dellaert, Richard Roberts
 */

#pragma once

#include <gtsam/base/types.h>
#include <gtsam/inference/FactorGraph.h>
#include <gtsam/inference/BayesNet.h>
#include <gtsam/inference/VariableIndex.h>
#include <gtsam/inference/Permutation.h>

#include <vector>
#include <deque>

namespace gtsam {

class Factor;
class Conditional;

	class Inference {
	private:
	  /* Static members only, private constructor */
	  Inference() {}

	public:

	  /**
	   * Eliminate a factor graph in its natural ordering, i.e. eliminating
	   * variables in order starting from 0.
	   */
	  template<class FactorGraph>
	  static typename FactorGraph::bayesnet_type::shared_ptr Eliminate(const FactorGraph& factorGraph);

    /**
     * Eliminate a factor graph in its natural ordering, i.e. eliminating
     * variables in order starting from 0.  Special fast version for symbolic
     * elimination.
     */
	  template<class Factor>
    static BayesNet<Conditional>::shared_ptr EliminateSymbolic(const FactorGraph<Factor>& factorGraph);

	  /**
	   * Eliminate a factor graph in its natural ordering, i.e. eliminating
	   * variables in order starting from 0.  Uses an existing
	   * variable index instead of building one from scratch.
	   */
	  template<class FactorGraph>
	  static typename FactorGraph::bayesnet_type::shared_ptr Eliminate(
	      FactorGraph& factorGraph, typename FactorGraph::variableindex_type& variableIndex);

	  /**
	   * Partially eliminate a factor graph, up to but not including the given
	   * variable.
	   */
    template<class FactorGraph>
    static typename FactorGraph::bayesnet_type::shared_ptr
    EliminateUntil(const FactorGraph& factorGraph, Index bound);

    /**
     * Partially eliminate a factor graph, up to but not including the given
     * variable.  Use an existing variable index instead of building one from
     * scratch.
     */
    template<class FactorGraph>
    static typename FactorGraph::bayesnet_type::shared_ptr
    EliminateUntil(FactorGraph& factorGraph, Index bound, typename FactorGraph::variableindex_type& variableIndex);

	  /**
	   * Eliminate a single variable, updating an existing factor graph and
	   * variable index.
	   */
    template<class FactorGraph>
    static typename FactorGraph::bayesnet_type::sharedConditional
    EliminateOne(FactorGraph& factorGraph, typename FactorGraph::variableindex_type& variableIndex, Index var);

    /**
     * Eliminate a single variable, updating an existing factor graph and
     * variable index.  This is a specialized faster version for purely
     * symbolic factor graphs.
     */
    static boost::shared_ptr<Conditional>
    EliminateOneSymbolic(FactorGraph<Factor>& factorGraph, VariableIndex<>& variableIndex, Index var);

    /**
     * Eliminate all variables except the specified ones.  Internally this
     * permutes these variables to the end of the ordering, eliminates all
     * other variables, and then undoes the permutation.  This is
     * inefficient if multiple marginals are needed - in that case use the
     * BayesTree which supports efficiently computing marginals for multiple
     * variables.
     */
    template<class FactorGraph, class VarContainer>
    static typename FactorGraph::bayesnet_type::shared_ptr Marginal(const FactorGraph& factorGraph, const VarContainer& variables);

    /**
     * Compute a permutation (variable ordering) using colamd
     */
    template<class VariableIndexType>
    static boost::shared_ptr<Permutation> PermutationCOLAMD(const VariableIndexType& variableIndex) { return PermutationCOLAMD(variableIndex, std::vector<Index>()); }
    template<class VariableIndexType, typename ConstraintContainer>
    static boost::shared_ptr<Permutation> PermutationCOLAMD(const VariableIndexType& variableIndex, const ConstraintContainer& constrainLast);

//    /**
//     * Join several factors into one.  This involves determining the set of
//     * shared variables and the correct variable positions in the new joint
//     * factor.
//     */
//    template<class FactorGraph, typename InputIterator>
//    static typename FactorGraph::shared_factor Combine(const FactorGraph& factorGraph,
//        InputIterator indicesBegin, InputIterator indicesEnd);


	};

	// ELIMINATE: FACTOR GRAPH -> BAYES NET

//	/**
//   * Eliminate a single node yielding a Conditional
//   * Eliminates the factors from the factor graph through findAndRemoveFactors
//   * and adds a new factor on the separator to the factor graph
//   */
//	template<class Factor, class Conditional>
//	boost::shared_ptr<Conditional>
//	eliminateOne(FactorGraph<Factor>& factorGraph, Index key);
//
//	/**
//	 * eliminate factor graph using the given (not necessarily complete)
//	 * ordering, yielding a chordal Bayes net and (partially eliminated) FG
//	 */
//	template<class Factor, class Conditional>
//	BayesNet<Conditional> eliminate(FactorGraph<Factor>& factorGraph, const Ordering& ordering);

	// FACTOR/MARGINALIZE: BAYES NET -> FACTOR GRAPH

//	/**
//	 * Factor P(X) as P(not keys|keys) P(keys)
//	 * @return P(not keys|keys) as an incomplete BayesNet, and P(keys) as a factor graph
//	 */
//	template<class Factor, class Conditional>
//	std::pair< BayesNet<Conditional>, FactorGraph<Factor> >
//	factor(const BayesNet<Conditional>& bn, const Ordering& keys);
//
//	/**
//	 * integrate out all except ordering, might be inefficient as the ordering
//	 * will simply be the current ordering with the keys put in the back
//	 */
//	template<class Factor, class Conditional>
//	FactorGraph<Factor> marginalize(const BayesNet<Conditional>& bn, const Ordering& keys);

	/**
	 * Hacked-together function to compute a Gaussian marginal for the given variable.
	 * todo: This is inefficient!
	 */
	//std::pair<Vector,Matrix> marginalGaussian(const GaussianFactorGraph& fg, const Symbol& key);

} /// namespace gtsam
