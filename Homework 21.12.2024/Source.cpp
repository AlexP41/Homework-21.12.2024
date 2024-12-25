/*
ВКАЗІВНИКИ та ДИНАМІЧНА ПАМ'ЯТЬ (new/delte)
===============================


№1

	Дано два масиви: А[M] і B[N] (M і N вводяться з клавіатури).
	Необхідно створити третій масив мінімально можливого розміру,
	у якому потрібно зібрати елементи масиву A, які не включаються до масиву B, без повторень.

Приклад:
	A=[1,2,3,4,3,2,1]
	B=[3,4,5,6]
Результат:
	Елементи A, яких немає в B: [1,2]



№2
	Дано два масиви: А[M] і B[N] (M і N вводяться з клавіатури).
	Необхідно створити третій масив мінімально можливого розміру,
	у якому потрібно зібрати елементи масивів A і B, які не є загальними для них, без повторень.
	Тобто потрібно сформувати третій масив, що містить тільки ті елементи, які унікальні для кожного з двох масивів, без дублювання.

Приклад:
	A=[1,2,3,4]
	B=[3,4,5,6]
Результат: [1,2,5,6]


№3
	Дано два масиви: А[M] і B[N] (M і N вводяться з клавіатури).
	Необхідно створити третій масив мінімально можливого розміру,
	у якому потрібно зібрати елементи обох масивів.


Навчальний матеріал
	https://fsx1.itstep.org/api/v1/files/Yayh8bbY4WDJDd0IGg5DHbdnQUQlQug_?inline=true

Результат роботи: посилання на GitHub
*/

#include <iostream>
#include <iomanip>
#include <locale>
#include <utility>

using namespace std;

void exercise(int exerciseNumber);

void autoFillArray(int length, int* arr);

void outputArray(int length, string arrayName, int* arr);

int userInputNumber(string arrayName);

template <typename T1, typename T2>
pair <T1*, int>  myFunc_1(int length1, int length2, T1* arr1, T2* arr2);

template <typename T1, typename T2>
pair<T1*, int> myFunc_2(int length1, int length2, T1* arr1, T2* arr2, bool outputText);

template <typename T1, typename T2>
pair<T1*, int> myFunc_3(int length1, int length2, T1* arr1, T2* arr2, bool outputText);

int main()
{
	system("chcp 1251>null");
	setlocale(LC_ALL, "ukr");

	srand(time(NULL));

	const int M = userInputNumber("M");
	const int N = userInputNumber("N");

	int* A = new int[M];
	int* B = new int[N];

	autoFillArray(M, A);
	outputArray(M, "M", A);

	autoFillArray(N, B);
	outputArray(N, "N", B);

	exercise(1);
	
	auto func_1Result = myFunc_1(M, N, A, B);

	int* resultArray_1 = func_1Result.first;

	outputArray(func_1Result.second, "Масив - результат", resultArray_1);

	exercise(2);

	auto func_2_1_Result = myFunc_2(M, N, A, B, true);
	auto func_2_2_Result = myFunc_2(N, M, B, A, false);

	int* resultArray_2_1 = func_2_1_Result.first;
	int* resultArray_2_2 = func_2_2_Result.first;

	int totalSize = func_2_1_Result.second + func_2_2_Result.second;
	int* ultimateResultForExercise_2 = new int[totalSize];


	for (int i = 0; i < func_2_1_Result.second; i++) {
		ultimateResultForExercise_2[i] = resultArray_2_1[i];
	}

	
	for (int i = 0; i < func_2_2_Result.second; i++) {

		// виникає попередження Buffer overrun while writing to 'ultimateResultForExercise_2'.   не розумію чому
		ultimateResultForExercise_2[func_2_1_Result.second + i] = resultArray_2_2[i];
	}

	outputArray(totalSize, "Масив - результат", ultimateResultForExercise_2);

	exercise(3);

	auto func_3_Result = myFunc_3(M, N, A, B, true);

	int* resultArray_3 = func_3_Result.first;

	outputArray(func_3_Result.second, "Масив - результат", resultArray_3);

	delete[] A;
	delete[] B;
	delete[] resultArray_1;
	delete[] resultArray_2_1;
	delete[] resultArray_2_2;
	delete[] ultimateResultForExercise_2;
	delete[] resultArray_3;
	return 0;
}


int userInputNumber(string arrayName)
{
	int userNum;

	while (true) 
	{
		cout << endl << "\033[033mВведіть ціле число для довжини \033[035m" << arrayName << "\033[033m масиву: \033[0m" << endl;
		cout << "\033[033mведіть ваш вибір: \033[0m";
		cin >> userNum;

		if (cin.fail()) 
		{
			cout << endl << "\033[031m Помилка! Будь ласка, введіть число.\033[0m\n" << endl;
			cin.clear(); 
			cin.ignore(1000, '\n'); 
			continue;
		}

		if (userNum < 1)
		{
			cout << endl << "\033[031m Помилка! Будь ласка, введіть ціле число більше за 0.\033[0m\n" << endl;
			continue;
		}
		
		break;
		
	}

	return userNum;
}

void exercise(int exerciseNumber)
{
	cout << endl << endl << "\t\t\t\t\033[032m Завдання  " << exerciseNumber << "\033[0m" << endl;
}

void autoFillArray(int length, int* arr)
{
	for (int i = 0; i < length; i++)
	{
		arr[i] = -10 + rand() % 21;
	}
}

void outputArray(int length, string arrayName, int* arr)
{
	cout << endl << "\t\t\t\t\033[033m Виведення масиву \033[035m" << arrayName << " \033[0m" << endl << endl;
	for (int i = 0; i < length; i++)
	{
		cout << setw(5) << arr[i];
	}
	cout << endl;
}

// EXERCISE 1
template <typename T1, typename T2>
pair<T1*, int> myFunc_1(int length1, int length2, T1* arr1, T2* arr2) {
	// Перевірка на різність типів
	if (!is_same<T1, T2>::value) {
		cout << endl << "\033[031mУВАГА! Типи масивів різні!\033[0m" << endl;
		return { nullptr, -1 };
	}

	T1* auxArray = new T1[length1];
	int count = 0;

	for (int i = 0; i < length1; i++) {
		bool isInArr2 = false;

		for (int j = 0; j < length2; j++) {
			if (arr1[i] == arr2[j]) {
				isInArr2 = true;
				break;
			}
		}

		if (!isInArr2) {
			bool alreadyInAux = false;
			for (int k = 0; k < count; k++) {
				if (arr1[i] == auxArray[k]) {
					alreadyInAux = true;
					break;
				}
			}

			if (!alreadyInAux) {
				auxArray[count] = arr1[i];
				count++;
			}
		}
	}

	T1* resultArray = new T1[count];
	for (int i = 0; i < count; i++) {
		resultArray[i] = auxArray[i];
	}

	cout << endl << "\033[032mНеобхідно створити третій масив мінімально можливого розміру,\n"
		            "у якому потрібно зібрати елементи масиву A, які не включаються до масиву B, без повторень.\033[0m" << endl;

	delete[] auxArray;

	return { resultArray, count };
}

// EXERCISE 2
template <typename T1, typename T2>
pair<T1*, int> myFunc_2(int length1, int length2, T1* arr1, T2* arr2, bool outputText) {
	// Перевірка на різність типів
	if (!is_same<T1, T2>::value) {
		cout << endl << "\033[031mУВАГА! Типи масивів різні!\033[0m" << endl;
		return { nullptr, -1 };
	}

	T1* auxArray = new T1[length1];
	int count = 0;

	for (int i = 0; i < length1; i++) {
		bool isInArr2 = false;

		for (int j = 0; j < length2; j++) {
			if (arr1[i] == arr2[j]) {
				isInArr2 = true;
				break;
			}
		}

		if (!isInArr2) {
			bool alreadyInAux = false;
			for (int k = 0; k < count; k++) {
				if (arr1[i] == auxArray[k]) {
					alreadyInAux = true;
					break;
				}
			}

			if (!alreadyInAux) {
				auxArray[count] = arr1[i];
				count++;
			}
		}
	}

	T1* resultArray = new T1[count];
	for (int i = 0; i < count; i++) {
		resultArray[i] = auxArray[i];
	}
	if (outputText)
	{

		cout << endl << "\033[032mНеобхідно створити третій масив мінімально можливого розміру,\n"
			            "у якому потрібно зібрати елементи масивів A і B, які не є загальними для них, без повторень.\n"
						"Тобто потрібно сформувати третій масив, що містить тільки ті елементи,\n"
						"які унікальні для кожного з двох масивів, без дублювання.\033[0m" << endl;
	}

	delete[] auxArray;

	return { resultArray, count };

}

// EXERCISE 3
template <typename T1, typename T2>
pair<T1*, int> myFunc_3(int length1, int length2, T1* arr1, T2* arr2, bool outputText) {
	// Перевірка на різність типів
	if (!is_same<T1, T2>::value) {
		cout << endl << "\033[031mУВАГА! Типи масивів різні!\033[0m" << endl;
		return { nullptr, -1 };
	}

	T1* mergedArray = new T1[length1 + length2];

	int count = 0;


	for (int i = 0; i < length1; i++) {
		mergedArray[count++] = arr1[i];
	}


	for (int i = 0; i < length2; i++) {
		bool isDuplicate = false;
		for (int j = 0; j < count; j++) {
			if (arr2[i] == mergedArray[j]) {
				isDuplicate = true;
				break;
			}
		}

		if (!isDuplicate) {
			mergedArray[count++] = arr2[i];
		}
	}

	if (outputText)
	{

		cout << endl << "\033[032mНеобхідно створити третій масив мінімально можливого розміру,\n"
			"у якому потрібно зібрати елементи обох масивів.\033[0m" << endl;
	}

	return { mergedArray, count };

}