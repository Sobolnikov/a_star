clear; xdel(winsid()); //Очистка рабочей области. Удаление графического окна 

size_ = 32;

//---------map------------
n_var = 30;
for j = 1:n_var
    map = zeros(size_,size_);
    
    map(1,:) = 1;       //borders
    map(size_,:) = 1;   //borders
    map(:,1) = 1;       //borders
    map(:,size_) = 1;   //borders
    
    obstacle = ones (4);
  
    for i = 1:14
        xg = int(28*rand(1,"uniform"))+1;
        yg = int(26*rand(1,"uniform"))+1;
        map(xg,yg:yg+4) = 1;
        xv = int(28*rand(1,"uniform"))+1;
        yv = int(26*rand(1,"uniform"))+1;
        map(xv:xv+4,yg) = 1;
    end
    
    s_pos = [3 3];  //start position
    e_pos = [30 30]; //end position
    
    map(s_pos(1),s_pos(2)) = -10;
    map(e_pos(1),e_pos(2)) = -10;

    deletefile('goo'+ string(j) +'.txt');
    write('goo'+ string(j) +'.txt',map,'(1(I3.1))');
end

figure(1); clf;
grayplot(1:size_,1:size_,map,rect=[0,0,size_+1,size_+1]);
hist3d(map);
