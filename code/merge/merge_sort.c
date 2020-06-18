// Combina i due sottoarray ordinati [p, q] e [q+1, r].
void merge(int *array, int p, int q, int r)
{
	int a, k = 0, i = p, j = q + 1;
	int *tempArray = malloc(sizeof(int) * (r - p + 1));  // not in place

	while (i <= q && j <= r)
	{
		if (array[i] < array[j])
			tempArray[k++] = array[i++];
		else
			tempArray[k++] = array[j++];
	}
	while (i <= q)
		tempArray[k++] = array[i++];   // ricopia il leftover sinistro (implica leftover destro vuoto)
	while (j <= r)
		tempArray[k++] = array[j++];   // ricopia il leftover destro (implica leftover sinistro vuoto)

	// ricopia i dati dall'array di appoggio in quello originale
	for (a = 0; a < k; a++)
		array[a + p] = tempArray[a];

	free(tempArray);
}

// Ordina l'array dall'indice p all'indice r inclusi
void mergeSort(int *data, int p, int r)
{
	int q = (p + r) / 2;           // si noti che in C la divisione tra interi memorizzata in variabile intera comporta il troncamento del numero all'intero inferiore (floor)
	if (p < r)
	{
		mergeSort(data, p, q);    // Ordina il sottoarray di sinistra
		mergeSort(data, q + 1, r);  // Ordina il sottoarray di destra
		merge(data, p, q, r);      // Combina i due sottoarray
	}
}