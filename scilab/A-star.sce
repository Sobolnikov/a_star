/////////////////////
////////A-star///////
/////////////////////
clear; xdel(winsid()); //Очистка рабочей области. Удаление графического окна 

size_ = 32;

function x = check_list(a, b)
    x = 0;
    for i = 1:length(b)
        if b(i)(1) == a(1) & b(i)(2) == a(2) then
            x = i;
        end
    end
endfunction

function x = min_list(a)
    y = zeros(length(a));
    for i = 1:length(a)
        y(i)=a(i)(3);
    end
    [z x] = min(y);
endfunction

//---------map------------
map = zeros(size_,size_);

map(1,:) = 1;       //borders
map(size_,:) = 1;   //borders
map(:,1) = 1;       //borders
map(:,size_) = 1;   //borders

map(6:16,13) = 1;   //obstacle
map(16,14:22) = 1;   //obstacle
map(6:16,23) = 1;   //obstacle

s_pos = [6 19];  //start position
e_pos = [17 23]; //end position

map(s_pos(1),s_pos(2)) = -10;
map(e_pos(1),e_pos(2)) = -10;

kg = 0;
kh = 1;

map1 = map;

open_list = list([s_pos(1) s_pos(2) 0 0 0 0]);
close_list = list();

while check_list([e_pos(1) e_pos(2)], open_list) == 0
    
    a = min_list(open_list);
    
    c = [open_list(a)(1) open_list(a)(1)+1 open_list(a)(1)-1;
         open_list(a)(2) open_list(a)(2)+1 open_list(a)(2)-1];
    
    g = open_list(a)(4)+1;
    
    if map(c(1,2), c(2,1))~=1 & check_list([c(1,2) c(2,1)], close_list) == 0 then 
        index = check_list([c(1,2) c(2,1)], open_list);
        h = abs(e_pos(1) - c(1,2))+abs(e_pos(2) - c(2,1));
        f = kg*g+kh*h;
        if index == 0 then 
            open_list($+1) = [c(1,2) c(2,1) f g c(1,1) c(2,1)];
        elseif open_list(index)(3) > f then
            open_list(index)(3) = f;
            open_list(index)(4) = g;
            open_list(index)(5) = c(1,1);
            open_list(index)(6) = c(2,1);
        end
    end
    
    if map(open_list(a)(1), open_list(a)(2)+1)~=1 & check_list([open_list(a)(1) open_list(a)(2)+1], close_list) ==0 then 
        index = check_list([open_list(a)(1) open_list(a)(2)+1], open_list);
        if index == 0 then 
            h = abs(e_pos(1) - c(1,1))+abs(e_pos(2) - c(2,2));
            f = kg*g+kh*h;
            open_list($+1) = [open_list(a)(1) open_list(a)(2)+1 f g c(1,1) c(2,1)];      
        elseif open_list(index)(3) > f then
            open_list(index)(3) = f;
            open_list(index)(4) = g;
            open_list(index)(5) = c(1,1);
            open_list(index)(6) = c(2,1);
        end
    end
    
    if map(open_list(a)(1)-1, open_list(a)(2))~=1 & check_list([open_list(a)(1)-1 open_list(a)(2)], close_list) == 0 then 
        index = check_list([open_list(a)(1)-1 open_list(a)(2)], open_list);
        if index == 0 then 
            h = abs(e_pos(1) - c(1,3))+abs(e_pos(2) - c(2,1));
            f = kg*g+kh*h;
            open_list($+1) = [open_list(a)(1)-1 open_list(a)(2) f g c(1,1) c(2,1)];      
        elseif open_list(index)(3) > f then
            open_list(index)(3) = f;
            open_list(index)(4) = g;
            open_list(index)(5) = c(1,1);
            open_list(index)(6) = c(2,1);
        end
    end
    
    if map(open_list(a)(1), open_list(a)(2)-1)~=1 &  check_list([open_list(a)(1) open_list(a)(2)-1], close_list) == 0 then
        index = check_list([open_list(a)(1) open_list(a)(2)-1], open_list);
        if index == 0 then
            h =  g+abs(e_pos(1) - c(1,1))+abs(e_pos(2) - c(2,3));
            f = kg*g+kh*h;
            open_list($+1) = [open_list(a)(1) open_list(a)(2)-1 f g c(1,1) c(2,1)];      
        elseif open_list(index)(3) > f then
            open_list(index)(3) = f;
            open_list(index)(4) = g;
            open_list(index)(5) = c(1,1);
            open_list(index)(6) = c(2,1);
        end
    end

    close_list($+1) = open_list(a);
    map(open_list(a)(1), open_list(a)(2)) = open_list(a)(3);
    open_list(a) = null();
end

close_list($+1) = open_list($);
path = list(close_list($));

while check_list([s_pos(1) s_pos(2)], path) == 0
    path($+1) = close_list (check_list([path($)(5) path($)(6)], close_list));
    map1(path($)(1), path($)(2)) = 10;
end

figure(1); clf;
grayplot(1:size_,1:size_,map,rect=[0,0,size_+1,size_+1]);
hist3d(map);


figure(2); clf;
grayplot(1:size_,1:size_,map1,rect=[0,0,size_+1,size_+1]);
hist3d(map1);
