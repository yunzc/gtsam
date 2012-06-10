% VisualISAMPlot: plot current state of visualSLAM::iSAM object
% Authors: Duy Nguyen Ta and Frank Dellaert

% global variables, input
global data frame_i isam result

% options
global CAMERA_INTERVAL DRAW_TRUE_POSES SAVE_FIGURES SAVE_GRAPHS
global SAVE_GRAPH PRINT_STATS

%% Plot results
h=gca;
cla(h);
hold on;
for j=1:size(data.points,2)
    point_j = result.point(symbol('l',j));
    plot3(point_j.x, point_j.y, point_j.z,'marker','o');
    if (frame_i>1) 
        P = isam.marginalCovariance(symbol('l',j));
        covarianceEllipse3D([point_j.x;point_j.y;point_j.z],P); 
    end
end
for ii=1:CAMERA_INTERVAL:frame_i
    pose_ii = result.pose(symbol('x',ii));
    if (frame_i>1)
        P = isam.marginalCovariance(symbol('x',ii));
    else 
        P = [];
    end
    plotPose3(pose_ii,P,10);
    if DRAW_TRUE_POSES % show ground truth
        plotPose3(data.cameras{ii}.pose,0.001*eye(6),10);
    end
end
axis([-40 40 -40 40 -10 20]);axis equal
view(3)
colormap('hot')

if SAVE_FIGURES
    fig2 = figure('visible','off');
    newax = copyobj(h,fig2);
    colormap(fig2,'hot');
    set(newax, 'units', 'normalized', 'position', [0.13 0.11 0.775 0.815]);
    print(fig2,'-dpng',sprintf('VisualiSAM%03d.png',frame_i));
end
if SAVE_GRAPHS && (frame_i>1)
    isam.saveGraph(sprintf('VisualiSAM%03d.dot',frame_i));
end

if SAVE_GRAPH
    isam.saveGraph(sprintf('VisualiSAM.dot',frame_i));
end

if PRINT_STATS
    isam.printStats();
end

drawnow