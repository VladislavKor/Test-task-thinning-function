#include <iostream>
#include <vector>

using namespace std;

void print(vector<pair<int, int>>& data);
void thinning(vector<pair<int, int>>& data, int n = 3); // функци€ прореживани€, может выкинуть исключение

int main()
{
	// формируем вектор значений
	vector<pair<int, int>> data;
	data.push_back({ 1, 10 }); //10
	data.push_back({ 2, 11 });
	data.push_back({ 3, 11 });
	data.push_back({ 4, 11 });
	data.push_back({ 5, 11 });
	data.push_back({ 6, 10 }); //10
	data.push_back({ 7, 11 });
	data.push_back({ 8, 11 });
	data.push_back({ 9, 11 });
	data.push_back({ 10, 11 });
	data.push_back({ 11, 10 }); //10

	cout << "Initial: ";
	print(data);

	try
	{
		thinning(data, 4); 
	}
	catch (int n)
	{
		cerr << "\nExeption: " << n << " < 3" << endl;
	}

	cout << "\n\nResult: ";
	print(data);

	return 0;
}

void print(vector<pair<int, int>>& data)
{
	for (auto& currentPair : data)
		cout << "(" << currentPair.first << ", " << currentPair.second << ") ";
}

void thinning(vector<pair<int, int>>& data, int n)
{
	// в случае n < 3 выбрасываем исключение со значением n
	if (n < 3)
	{
		throw n;
		return;
	}

	int s = data.size(); 
	int start = 0; // индекс элемента €вл€ющегос€ началом подпоследовательности
	int stop = 0; // индекс элемента конца подпоследовательности
	for (size_t i = 1; i < s; i++)
	{
		// определ€ем конец подпоследовательности
		if (data[i - 1].second != data[i].second)
		{
			stop = i - 1;
			// если подпоследовательность всего из одного символа
			if (stop == start)
			{
				start = stop + 1;
			}
			// если подпоследовательность из двух символов
			else if (stop - start == 1)
			{
				// поступаем аналогично
				start = stop + 1;
			}
			// если подпоследовательность из 3 символов
			else if (stop - start == 2)
			{
				// удалем второй элемент подпоследовательности
				data.erase(data.begin() + start + 1);
				s--;
				start += 2;
				i--;
			}
			// если подпоследовательность более чем из 3 символов
			else if (stop - start > 2)
			{
				int offset = 1;
				for (size_t j = 2; j <= stop - start; j++)
				{
					if (j % n != 0)
					{
						data.erase(data.begin() + start + offset);
						s--;
						i--;
					}
					else
						offset++;
				}
				start += offset + 1;
			}
		}
	}
}
