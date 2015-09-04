function MyVector()
    mas = [12 8 9 1 4 5];
    last = length(mas);
	k = 0;
	k = input('1) print \n2) sort_shell \n3) sort_merge \n4) cort_case \n5) find_fibonachi \n6) find_direct \n7) rand_fill \n Enter to 8 for exit\n');
	while (k ~= 8)
        Start = cputime();
        if k == 1
            myPrint(mas);
            pause();
        end
        if k == 2
            disp('Method Shell');
            mas = sortShell(mas);
            pause();
        end
        if k == 3
            disp('Method merge');
            mas = sort_merge(mas);
            pause();
        end
        if k == 4
            disp('Method sort_case');
            mas = sortCase(mas);
            pause();
        end
        if k == 5
            n = input('enter to n: ');
            key = input('nenter to key: ');
            result = find_fibonachi(n, key, mas) + 1
            pause();
        end
        if k == 6
            t = input('enter to key: ');
            result = findDirection(mas, t)
            pause();
        end
        if k == 7
            mas = myRand(mas);
            disp('random');
            pause();
        end
        if k == 8
            break;
        end
        Time = cputime() - Start
        pause();
        k = input('1) print \n2) sort_shell \n3) sort_merge \n4) cort_case \n5) find_fibonachi \n6) find_direct \n7) rand_fill \n Enter to 8 for exit\n');
    end
end

function myPrint(mas) %output to the screen
    mas
end

function mas = myRand(mas) %vector fills randomly numbers
    mas = rand(1, length(mas));
end

function result = number_fib(n) %calculate the number of fibbonachi
    f1 = 0;
    f2 = 0;
    result = 0;
    if (n == 0) || (n == 1)
        result = n;
        return;
    else
        if n >= 2
            f1 = number_fib(n - 1);
            f2 = number_fib(n - 2);
            result = f1 + f2;
            return
        end
    end
end

function mid = find_fibonachi(n, key, mas)% find by Fibbonachi
		t = 0;
        search = 0;
        mid = 0;
        i = 0;
        c = 0;
		f1 = 0;
        f2 = 0;
		j = 1;
        s = 0;
		while (number_fib(j) < (n + 1))
			j = j + 1;
        end
		mid = n - number_fib(j - 2) + 1;
		f1 = number_fib(j - 2);
		f2 = number_fib(j - 3);
		c = 0;
		for s = 0:s>=0
			if (c == 1)
				break;
            end
			if (mid > 0)
                if (key == mas(mid))
                    break;
                end
            end
			if ((mid <= 0) || (key > mas(mid)))
				if (f1 == 1)
					c = 1;
                else
					mid = mid + f2;
					f1 = f1 - f2;
					f2 = f2 - f1;
                end
            else
				if (f2 == 0)
					c = 1;
                else
					mid = mid - f2;
					t = f1 - f2;
					f1 = f2;
					f2 = t;
                end
            end
            s = s + 1;
        end
		if (c == 1) 
			search = 0;
		else 
			search = mid;
        end
		if ((search == 0) || (search == n)) 
			disp('number is not found');
            pause();
			return;
		else
			return;
        end
end

function mas = sortShell(mas)%method by Shell
    e = 0;
    comp = 0;
    size = numel(mas);
    step = round(size/2);
    while step > 0
        comp = comp + 1;
        for i = (step+1:size)
            temp = mas(i);
            j = i;
            while (j >= step+1) && (mas(j-step) > temp)
                mas(j) = mas(j-step);
                j = j - step;
                comp = comp + 1;
                comp = comp + 1;
                e = e + 1;
                e = e + 1;
            end
            mas(j) = temp;
 
        end 
 
        if step == 2 
            step = 1;
        else
            step = round(step/2.2);
        end        
    end 
    e
    comp
end 

function mas = sort_merge(mas)
 
    if numel(mas) <= 1
        return
    else
        middle = ceil(numel(mas) / 2);
        left = mas(1:middle);
        right = mas(middle+1:end);
 
        left = sort_merge(left);
        right = sort_merge(right);
 
        if left(end) <= right(1)
            mas = [left right];
            return
        end
        %merge(left,right)
        c = 1;
        while (numel(left) > 0) && (numel(right) > 0)
            if(left(1) <= right(1))
                mas(c) = left(1);
                left(1) = [];
            else
                mas(c) = right(1);
                right(1) = [];
            end           
            c = c + 1;   
        end
 
        if numel(left) > 0
            mas(c:end) = left;
        elseif numel(right) > 0
            mas(c:end) = right;
        end        
    end 
end 

function mas = sortCase(mas) %method case 
    count = length(mas);
    for i=1:(count - 1)  
        min = i;
        for j =(i+1):count
            if mas(min) > mas(j) 
                min = j;
            end
        end
        if min~=i 
           t=mas(i);
           mas(i)= mas(min);
           mas(min)= t;    
        end
    end
end

function index = findDirection(mas, number)
    index = 1;
    it = 1;
    for it = 1:length(mas)-1
       if mas(it) == number
           return;
       else
           index = index + 1;
       end
    end
end