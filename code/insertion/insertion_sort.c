void insertionSort(int *data, int n)
{
	int i, j, key;

	//ciclo esterno
	for (j = 1; j < n; j++)
	{
		key = data[j];
		i = j - 1;
		//ciclo interno (sottoarray da ordinare)
		while (i >= 0 && data[i] > key)
		{
			data[i + 1] = data[i];
			i--;
		}
		data[i + 1] = key;
	}
}