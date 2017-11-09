
#define CUTOFF 8
#define N 10

template <class T>
void swap(T* a, T* b)
{
	T buffer = *a;
	*a = *b;
	*b = buffer;
}

template <class T>
void shuffle(T *array, int size)
{
    int j;
    if (size > 1) 
    {
        for (int i = 0; i < size - 1; i++) 
        {
          j = i + rand() / (RAND_MAX / (size - i) + 1);
          T buffer = array[j];
          array[j] = array[i];
          array[i] = buffer;
        }
    }
}

template <class T>
void insertionSort(T* array, T size)
{
    int i, j;
    T key;
    for (int i = 1; i < size; i++)
    {
        key = array[i];
        j = i;
        while (j >= 1 && array[j-1] > key)
        {
            array[j] = array[j-1];
            j--;
        }
        array[j] = key;
    }
}

template <class T>
void subarrayInsertionSort(T* array, int begin, int end)
{
    int i, j;
    T key;
    for (int i = begin + 1; i <= end; i++)
    {
        key = array[i];
        j = i;
        while (j >= begin + 1 && array[j-1] > key)
        {
            array[j] = array[j-1];
            j--;
        }
        array[j] = key;
    }
}

template <class T>
void shellSort(T* array, int size)
{
    int i, j;
    T key;
    for (int step = size/2; step > 0; step /= 2)
    {
        for (int i = step; i < size; i++)
        {
            key = array[i];
            j = i;
            while ( j >= step && array[j-step] > key)
            {
                array[j] = array[j-step];
                j -= step;
            }
            array[j] = key;
        }
    }
}

template <class T>
void bubbleSort(T* array, int size)
{
    bool exit = false;
    int j = 1;
    while(!exit)
    {
        exit = true;
        for (int i = 0; i < size-j; i++)
        {
            if (array[i] > array[i+1])
            {
                swap(array[i], array[i+1]);
                exit = false;
            }
        }
        j++;
    }
}

template <class T>
void selectionSort(T* array, int size)
{
    int min;
	for (int i = 0; i < size-1; i++)
	{
		min = i;
		for (int j = i + 1; j < size; j++)
		{
			if (array[j] < array[min])
	            min = j;
		}
	    swap(array[i], array[min]);
	}
}


// Merge begin
template <class T>
void merge(T* array, T* aux, int begin, int mid, int end)
{
    for (int i = begin; i <= end; i++)
        aux[i] = array[i];
    int j = begin, k = mid+1;
    for (int i = begin; i <= end; i++)
    {
        if (j > mid) array[i] = aux[k++];
        else if (k > end) array[i] = aux[j++];
        else if (aux[k] > aux[j])  array[i] = aux[j++];
        else array[i] = aux[k++];
    }
}

template <class T>
void sortM(T* array, T* aux, int begin, int end)
{
    if (begin >= end) return;
    if (begin + CUTOFF - 1 >= end)
	{ // Optimization for low size arrays with insertionSort.
	    subarrayInsertionSort(array, begin, end);
	    return;
	}
    int mid = begin + (end-begin)/2;
    sortM(array, aux, begin, mid);
    sortM(array, aux, mid+1, end);
    if (array[mid] < array[mid+1]) return; //It means 2 subarrays are sorted.
    merge(array, aux, begin, mid, end);
}

template <class T>
void mergeSort(T* array, int size)
{
    T* aux = new T[size];
    sortM(array, aux, 0, size-1);
}
//Merge end

// Qsort begin
template <class T>
int partition(T* array, int begin, int end)
{
	int i = begin, j = end+1;
	while(true)
	{
		while(array[++i] < array[begin])
			if (i == end) break;
		while(array[--j] > array[begin])
			if (j == begin) break;
		if (i >= j) break;
		swap(array[i], array[j]);
	}
	swap(array[j], array[begin]);
    return j;
}

template <class T>
void sortQ(T* array, int begin, int end)
{
	if (begin >= end) return;
	if (begin + CUTOFF - 1 >= end)
	{ // Optimization for low size arrays with insertionSort.
	    subarrayInsertionSort(array, begin, end);
	    return;
	}
	int p = partition(array, begin, end);
	sortQ(array, begin, p);
	sortQ(array, p+1, end);
}

template <class T>
void quickSort(T* array, int size)
{
    shuffle(array, size);
    sortQ(array, 0, size-1);
}
//Qsort end

int main()
{
   int array[N] = {7, 11, 28, 98, 21, 4, 92, 17, -80, 100};
   int* p = &array[0];
   quickSort(p, N);
   //shellSort(p, N);
   //bubbleSort(p, N);
   //insertionSort(p, N);
   //selectionSort(p, N);
   //mergeSort(p, N);
   for (int i = 0; i < N; i++)
        printf("%d ", array[i]);
   return 0;
}