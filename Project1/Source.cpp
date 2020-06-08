#include <iostream> 
#include <fstream> 
#include <locale.h> 
#include <limits> 
#include <thread>
#include <windows.h>
#undef max

using namespace std;
HANDLE hEvent, hEvent2;
HANDLE hThr;
HANDLE hSem, hSem2;
HANDLE hMut, hMut2;
int TypeSync = 0;
unsigned long uThrID;
double** buf;
int buf1;
HANDLE hRead, hWrite;
int get_variant() {

	int s; // Строка для считывания введённых данных   
	cin >> s; // Считываем строку   

   // Пока ввод некорректен, сообщаем об этом и просим повторить его   
	if (!cin)
		while (cin.fail()) {
			cout << "Incorrect input. Try again: " << endl; // Выводим сообщение об ошибке   
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> s; // Считываем строку повторно    
		}

	return s;
}

void inputInt(int &number, int parametr) {

	if (parametr == 1) {
		cin >> number;
		if (!cin || number <= 1)
			while (cin.fail() || number <= 1)
			{
				cout << "Некорректный ввод!"  << endl;
				cout << "Попробуйте снова."  << endl;
				cout << "Введите количество строк: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> number;
			}
	}
	else {
		cin >> number;
		if (!cin || number < 0)
			while (cin.fail() || number < 0)
			{
				cout << "Некорректный ввод!"  << endl;
				cout << "Попробуйте снова."  << endl;
				cout << "Введите количество строк: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> number;
			}
	}

}

double inputDouble() {
	double number;
	cin >> number;
	if (!cin)
		while (cin.fail())
		{
			cout <<"Некорректный ввод!"  << endl;
			cout <<"Попробуйте снова."  << endl;
			cout << "index[""][""]:";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> number;
		}
	return number;
}

void createArray(double **&index) {

	cout << "Введите количество строк: ";
	int n;
	inputInt(n, 1);
	double **nIndex = new double *[n];

	for (int i = 0; i < n; i++)
		nIndex[i] = new double[2];

	for (int i = 0; i < n; i++) // Цикл по строкам   
	{
		for (int j = 0; j < 2; j++)// Цикл по столбцам   
		{
			cout << "index[" << i << "][" << j << "]: ";
			nIndex[i][j] = inputDouble();
			cout << endl;
		}
	}
	WriteFile(hWrite, nIndex, (2*n*sizeof(double)), NULL, NULL);
	buf1 = n;

	delete[] index;
	index = nIndex;
	system("pause");
}

void showArray() {
	int n = buf1;
	double** index = new double*[10000000];
	for (int i = 0; i < n; i++)

		index[i] = new double[2];
	ReadFile(hRead, index, (2*n*sizeof(double)), NULL, NULL);

	cout << "Показать массив: "  << endl;
	cout << " X  Y " << endl;
	for (int i = 0; i < n; i++) // Цикл по строкам   
	{
		for (int j = 0; j < 2; j++) // Цикл по столбцам   
		{
			cout << " " << index[i][j] << " ";
		}
		cout << endl;
	}
	system("pause");
}

void saveArray(double **index) {
	ofstream fout("out.txt", ios::out);
	cout << "Сохраняем массив в файл."  << endl;
	int n = buf1;
	fout << "size: " << n << "\n";
	fout << "X\tY" << "\n";
	for (int i = 0; i < n; i++) // Цикл по строкам   
	{
		for (int j = 0; j < 2; j++) // Цикл по столбцам   
		{
			fout << index[i][j] << "\t";
		}
		fout << "\n";
	}
	cout << "Массив сохранен"  << endl;
	system("pause");
}

void loadArray(double **&index) {
	char skip[10];
	ifstream fin("out.txt", ios::in);
	cout << "Загружаем массив из файла: "  << endl;
	int n;
	fin >> skip >> n >> skip >> skip;

	double **nIndex = new double *[n];
	for (int i = 0; i < n; i++)
		nIndex[i] = new double[2];//Память   

	for (int i = 0; i < n; i++) // Цикл по строкам   
	{
		for (int j = 0; j < 2; j++) // Цикл по столбцам   
		{
			if (nIndex[i][j] = -6.27744e+66)
				nIndex[i][j] = 0;
			fin >> nIndex[i][j];
		}
	}
	delete[] index;
	index = nIndex;
	WriteFile(hWrite, nIndex, (2*n*sizeof(double)), NULL, NULL);
	buf1 = n;
	cout << "Массив загружен."  << endl;
	system("pause");
}

void editArray(double **&index) {
	char skip[10];
	int n;
	ifstream fin("out.txt", ios::in);
	fin >> skip >> n >> skip >> skip;
	cout <<"Изменяем размер массива: "  << endl;
	//Чтение данных из файла в динамический массив   

	cout << "Введите кол-во строк: ";
	cin >> n;

	cout << "Колличество столбцов: 2" << endl;

	double **nIndex = new double *[n];

	for (int i = 0; i < n; i++)
		nIndex[i] = new double[2];//Память   

			//Копируем массив из файла    
	for (int i = 0; i < n; i++) // Цикл по строкам    
	{
		for (int j = 0; j < 2; j++) // Цикл по столбцам   
		{
			if (nIndex[i][j] = -6.27744e+66)
				nIndex[i][j] = 0;
			fin >> nIndex[i][j];
		}
	}
	buf1 = n;
	//Изменяем   
	char c;
	do {
		int l, p;
		double h;
		getchar();
		cout <<"Изменить значения(y/n)?: "  << endl;
		c = getchar();
		if (c == 'y') {
			cout << "Введи строку по значению индекса = ";
			inputInt(l, 2);
			cout << "Введи столбец по значению индекса = ";
			inputInt(p, 2);
			cout << "Введи значение = ";
			h = inputDouble();
			nIndex[l][p] = h;
		}
	} while (c == 'y');

	cout << "Измененный массив:" << endl;
	cout << " X  Y " << endl;
	for (int i = 0; i < n; i++) // Цикл по строкам    
	{
		for (int j = 0; j < 2; j++) // Цикл по столбцам   
		{
			cout << " " << nIndex[i][j] << " ";
		}
		cout << endl;
	}
	delete[] index;
	index = nIndex;
	WriteFile(hWrite, nIndex, (2 * n * sizeof(double)), NULL, NULL);
	system("pause");
}
void shellSort() {
	if (TypeSync == 1) //Проверка на ввод переменной для выбора синхронизации 
	{
	
		WaitForSingleObject(hEvent, INFINITE);//Ожидаем сигнального состояния объекта, переданного в функцию 
	}
	else if (TypeSync == 2)
	{
		
		WaitForSingleObject(hSem, INFINITE);//Ожидаем сигнального состояния объекта, переданного в функцию  
	}
	else if (TypeSync == 3)
	{
		
		WaitForSingleObject(hMut, INFINITE);//Ожидаем сигнального состояния объекта, переданного в функцию  
	}
	int i, j, n, step;
	n = buf1;
	double **index = new double *[n];
    for (int i = 0; i < n; i++)
	index[i] = new double[2];
	
	ReadFile(hRead, index, (2*n*sizeof(double)), NULL, NULL);
	

	double t, m;

	for (step = n / 2; step > 0; step /= 2)

		for (i = step; i < n; i++)

		{

			t = index[i][0];

			m = index[i][1];

			for (j = i; j >= step; j -= step)

			{

				if (t < index[j - step][0]) {

					index[j][0] = index[j - step][0];

					index[j][1] = index[j - step][1];

				}

				else

					break;

			}
			index[j][0] = t;
			index[j][1] = m;
		}
	WriteFile(hWrite, index, (2*n*sizeof(double)), NULL, NULL);
	buf1 = n;
	cout << "Данные массива были отсортированы методом Шелла."  << endl;

}

double Newton(double x,  double *arrayX, double *arrayY, double step) {
	// Выделяем память под динамический двумерный массив dy  
	int n = buf1;
	double **temp = new double*[n];
	for (int i = 0; i < n; i++) temp[i] = new double[n];

	// Подсчитываем dy
	for (int i = 0; i < n; i++)
	{
		temp[0][i] = arrayY[i];
	}

	for (int i = 1; i < n; i++)//Цикл по всем значениям  
	{
		for (int j = 0; j < n - i; j++)
		{
			temp[i][j] = temp[i - 1][j + 1] - temp[i - 1][j];//Подсчет промежуточных значений  
		}
	}
	// Вычисляем y
	double q = (x - arrayX[0]) / step; // См. формулу  
	double result = arrayY[0]; // Результат (y)   

	double mult_q = 1; // Произведение из  q*(q-1)*(q-2)*(q-n)
	double fact = 1;  // // Факториал  
	for (int i = 1; i < n; i++)//Цикл по всем значениям  
	{
		fact *= i;
		mult_q *= (q - i + 1);

		result += mult_q / fact * temp[i][0];// Подсчет значений согласно формулам  
	}
	for (int i = 0; i < n; i++) delete[] temp[i];//Очистка памяти  
	delete[] temp;//

	return result;
}


void interpolation(double **index) {
	
	if (TypeSync == 1) //Проверка на ввод переменной для выбора синхронизации 
	{
		
		WaitForSingleObject(hEvent2, INFINITE);//Ожидаем сигнального состояния объекта, переданного в функцию 
	}
	else if (TypeSync == 2)
	{
		
		WaitForSingleObject(hSem2, INFINITE);//Ожидаем сигнального состояния объекта, переданного в функцию  
	}
	else if (TypeSync == 3)
	{
		
		WaitForSingleObject(hMut2, INFINITE);//Ожидаем сигнального состояния объекта, переданного в функцию  
	}
	int rows = buf1;
	double** array = new double*[rows];
	for (int i = 0; i < rows; i++)

		array[i] = new double[2];

	ReadFile(hRead, array, (2*rows*sizeof(double)), NULL, NULL);


	ofstream fout("out2.txt", ios::out);
	double *arrayX = new double[rows];//Выделение памяти под под массив  
	double *arrayY = new double[rows];

	for (int i = 0; i < rows; i++) {//Разбиваем массив на два массива  
		arrayX[i] = array[i][0];
		arrayY[i] = array[i][1];
	}
	double y;
	cout << "X\tY";
	fout << "X\tY" << "\n";
	for (double x = arrayX[0]; x <= arrayX[rows - 1]; x += 0.1)
	{
		y = Newton(x, arrayX, arrayY, 1);//Вывод  Х и У после интерполяции  

		cout << "\n"
			<< x
			<< "\t"
			<< y
			<< endl;
		fout << x << "\t" << y << "\n";
	}

}


void print_menu() {
	system("cls"); // Очищаем экран    
	cout <<"|=============МЕНЮ================|" << endl
		<< "|1.Создать массив.                |" << endl
		<< "|2.Показать массив.               |" << endl
		<< "|3.Сохранить массив в файл.       |" << endl
		<< "|4.Изменить сохраненный массив.   |" << endl
		<< "|5.Отсортировать массив.          |" << endl
		<< "|6.Интерполяция методом Ньютона.  |" << endl
		<< "|7.Загрузить массив из файла.     |" << endl
		<< "|8.Exit.                          |" << endl
		<< "|=================================|" << endl
		<< ">";
}

int main()
{
	setlocale(LC_ALL, "rus");
	 int m ,sec,vvod;
	 cout << "1)Программа будет запускаться через определенное колличество минут." << endl;
	 cout << "2)Программа будет запускаться через определенное колличество секунд." << endl;
	 cout << "<<";
	 cin >> vvod;
	 system("cls");
	 if (vvod==1)
	 {
		 cout << "Через сколько минут должна запуститься программа:";
		 cin >> m;
		 for (int min = m; min > 0; min--)
		 {
			 for ( sec = 59; sec >= 0; sec--)
			 {
				 Sleep(1000);
				 cout << "\r" << min << "\t" << sec;
			 }
		 }
	 }
	 else 
	 {
		 cout << "Через сколько секунд должна запуститься программа:";
		 cin >> sec;
		 for (sec ; sec >= 0; sec--)
		 {
			 Sleep(1000);
			 cout << "\r"  << "Таймер:\t" << sec;
		 }
	 }
	
	system("cls");
	cout << "1 - Events" << endl << "2 - Semaphore" << endl << "3 - Mutex" << endl;
	cout << "Выберите необходимый тип синхронизации:";
	cin >> TypeSync;
	
	int n = 0;
	double **index = new double *[0];
	for (int i = 0; i < 0; i++)
		index[i] = new double[0];

	int variant; // Выбранный пункт меню   

	char c;
	CreatePipe(&hRead, &hWrite, NULL, 0);
	while (1) {
		print_menu(); // Выводим меню на экран variant variant = get_variant(5); // Получаем номер выбранного пункта меню   

		variant = get_variant(); // Получаем номер выбранного пункта меню   

		switch (variant) {
			//=======================================================================// 
		case 1:
		{
			//Создать массив  
			createArray(index);
			break;
		}
		//=================================================// 
		case 2:
		{
			//Показать созданный массив  
			showArray();
			break;
		}
		//=================================================// 
		case 3:
		{
			//Сохранить массив в файл  
			saveArray(index);
			break;
			//=================================================// 
		}
		case 4:
		{
			//Изменить массив  
			editArray(index);
			break;
		}
		//=================================================// 
		case 5:
		{
			//Сортировка   
			if (TypeSync == 1) //Проверка на ввод переменной для выбора синхронизации 
			{
				hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
				hThr = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)shellSort, NULL, 0, &uThrID);//Создание потоков  
				SetEvent(hEvent);
				system("pause");
				CloseHandle(hEvent);//Закрытие хэндла  
			}
			else if (TypeSync == 2)
			{
				hSem = CreateSemaphore(NULL, 0, 1, NULL);//Создание семафор  
				hThr = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)shellSort, NULL, 0, &uThrID);//Создание потоков 
				ReleaseSemaphore(hSem, 1, 0);
				system("pause");
				CloseHandle(hSem);//Закрытие хэндла  
			}
			else if (TypeSync == 3)
			{
				hMut = CreateMutex(NULL, TRUE, "First step");//Создание мьютексов 
				hThr = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)shellSort, NULL, 0, &uThrID);//Создание потоков 
				ReleaseMutex(hMut);
				system("pause");
				CloseHandle(hMut);//Закрытие хэндла  
			}
			break;
			system("pause");
			system("cls");
			break;
		}
		//=================================================// 
		case 6:
		{
			//Интерполяция  
			if (TypeSync == 1) //Проверка на ввод переменной для выбора синхронизации 
			{
				hEvent2 = CreateEvent(NULL, FALSE, FALSE, NULL);
				hThr = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)interpolation, NULL, 0, &uThrID);
				SetEvent(hEvent2);
				system("pause");
				CloseHandle(hEvent2);//Закрытие хэндла  
			}
			else if (TypeSync == 2)
			{
				hSem2 = CreateSemaphore(NULL, 0, 1, NULL);
				hThr = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)interpolation, NULL, 0, &uThrID);
				ReleaseSemaphore(hSem2, 1, 0);
				system("pause");
				CloseHandle(hSem2);//Закрытие хэндла  
			}
			else if (TypeSync == 3)
			{
				hMut2 = CreateMutex(NULL, TRUE, "Second step");
				hThr = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)interpolation, NULL, 0, &uThrID);
				ReleaseMutex(hMut2);
				system("pause");
				CloseHandle(hMut2);//Закрытие хэндла  
			}
			break;
			Sleep(1500);
			system("pause");
			system("cls");
			break;
		}
		//=================================================// 
		case 7:
		{
			//Загрузить массив из файла  
			loadArray(index);
			break;
		}
		case 8:
			system("pause");
			return 0;

		default: {
			cout << "Введен несуществующий пункт меню !"  << endl;
			cout << "Попробуйте снова."  << endl;
			system("pause");
			break;
		}
		}


}
}




