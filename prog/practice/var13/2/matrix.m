function matrix()
    a = [4 5 6; 1 2 3; 7 8 9]
    a = [0 0 0; 0 0 0; 0 0 0]
    %a = round(rand(0, 20))
    %[b, i, j] = inputFile('matrix2.txt')
    %b = read('./matrix2,txt')
    b = [1 2 3; 4 5 6; 7 8 9]
    b = round(rand(15));
    a = b;
    %result = individualFind(a)
    b = load('matrix2.txt')
    outputFile(a, 3, 3, 'matrix2.txt')
    key = input('Меню:\n1)ввод матрицы с клавиатуры\n2)сложение матриц\n3)вычитание матриц\n4)умножение матриц\n5)транспонирование матрицы\n6)Индивидуальное задание(вариант №13):\n7)для выхода\n')
    while (key > 0)
        if key == 1
            a = ReadKeyboard();
            %read('matrix2.txt')
            outputFile(a, length(a), length(a), 'matrix2.txt');
        end
        if key == 2
            fprintf('матрица ');
            a
            fprintf('матрица ');
            b
            if length(a) == length(b)
                disp('сумма матриц c равна:');
                c = a + b
            else
                disp('ОШИБКА! матрицы должны быть одинакового размера')
                key = input('Меню:\n1)ввод матрицы с клавиатуры\n2)сложение матриц\n3)вычитание матриц\n4)умножение матриц\n5)транспонирование матрицы\n6)Индивидуальное задание(вариант №13):\n7)для выхода\n')
                %pause();
                continue;
            end
        end
        if key == 3
            fprintf('матрица ');
            a
            fprintf('матрица ');
            b
        if length(a) == length(b)

                disp('сумма матриц c равна:');
                c = a + b
            else
                disp('ОШИБКА! матрицы должны быть одинакового размера')
                key = input('Меню:\n1)ввод матрицы с клавиатуры\n2)сложение матриц\n3)вычитание матриц\n4)умножение матриц\n5)транспонирование матрицы\n6)Индивидуальное задание(вариант №13):\n7)для выхода\n')
                %pause()
                continue;
            end
        end
        if key == 4
            fprintf('матрица ');
            a
            fprintf('матрица ');
            b
            disp('произведение матриц c равна:');
            c = a * b
        end
        if key == 5
            fprintf('матрица ');
            a
            disp('транспонированная матрица равна:');
            a'
        end
        if key == 6
            fprintf('матрица ');
            a
            disp('Размер матрицы по одному измерению: ');
            result = individualFind(a);
            disp(result);
        end
        if key == 7
            break;
        end
        %pause()
        key = input('Меню:\n1)ввод матрицы с клавиатуры\n2)сложение матриц\n3)вычитание матриц\n4)умножение матриц\n5)транспонирование матрицы\n6)Индивидуальное задание(вариант №13):\n7)для выхода\n')
    end
end

function print(matrix)
    matrix
end

function c = ReadKeyboard()
    c = input('Введите матрицу:');
    disp('Ваша матрица: ');
    print(c);
end

function c = read(file)
    [f,c] = fopen(file, 'rt');
    if f ~=-1
        c = ' ';
        while feof(f) == 0
            line = fgetl(f);
            c = char(c, line);
        end
        fclose(f);
    end
end

function [ c, n, m ] = inputFile(file)
    f = fopen(file, 'rt');
    n = fscanf(f,'%d',1);
    m = fscanf(f,'%d',1);
    for i=1:n
        for j=1:m
            c(i,j) = fscanf(f,'%f',1);
        end
    end
    fclose(f);
end

function outputFile( c, n, m, file)
    f = fopen(file, 'wt');
    for i=1:n
        for j=1:m
            fprintf(f,'%f\t',c(i,j));
        end
        fprintf(f,'\n');
    end
    fclose(f);
end

function c = individualFind(m)
    [rows, cols] = size(m);
    max = 0;
    for i = 1:cols
        for j = 1:rows
            k = 1;
            while (isCorrect(m, i, j, k - 1) == true)
                if (max < k)
                    max = k;
                end
                k = k + 1;
            end
        end
    end
    c = max;
end


function c = isCorrect (m, rowFirst, colFirst, sizeS)
    [rows, cols] = size(m);
    if (((rowFirst + sizeS) > rows) || ((colFirst + sizeS) > cols))
        c = false;
        return;
    end
    for i = 0:sizeS
        if ((m(rowFirst + sizeS, colFirst + i) ~= 0) || (m(rowFirst + i, colFirst + sizeS) ~= 0))
            c = false;
            return;
        end
    end
    c = true;
end
