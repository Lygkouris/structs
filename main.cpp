#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<chrono>

using namespace std;
using namespace std::chrono;

class Structure{
public:
  int num;
  string string1;
  string string2;
  string string3;
  //gia na mporesoume na dhmiourgisoume ena array typou class Structure
  //tha prepei na ftiaksoume enan dummy constructor
  Structure(){}
  Structure(int number,string s1,string s2,string s3){
    num=number;
    s1=string1;
    s2=string2;
    s3=string3;
  }
};

void write_file(double array[],int n,FILE *file);
void display(double array[],int n);
void swap(int *x,int *y);
int locOfSmallest(Structure b[],int s,int e);
void selectionSort(Structure b[],int n);
void bubble(Structure b[],int n);
void bubbleSort(Structure b[],int n);
void insertionSort(Structure b[],int n);
void mergeSort(Structure b[],int n );
void mergeSortRecursion(Structure b[],int l,int r);
void mergeSortedArrays(Structure b[],int l,int m,int r);
void quickSort(Structure b[],int left,int right);
void shellSort(Structure b[],int n);
void heapify(Structure b[], int n, int i);
void heapSort(Structure b[], int n);

int main(){
  Structure array_str[100];
  //perasma tyxaiwn dedomenwn apo to file sto pinaka array_str
  fstream rand_data;
  rand_data.open("rand_data.csv",ios::out);
  //dhmiourgia object gia kathe xwra kai apo8hkeysei tou sto pinaka countries[199]
	vector<string> row;
	for(int i=0;i<100;i++){
		row.clear();
		//h katalhksh .clear() katharizei to vector
		string line,word;
		getline(rand_data,line);
		stringstream s(line);
		while (getline(s,word,','))
			row.push_back(word);
    //to vector apo8hkeyei string data,ara to row[0] pou periexei ton akeraio arithmo prepei na metatrapei apo string se int
    int a=stoi(row[0]);
		array_str[i]=Structure(a,row[1],row[2],row[3]);
	}

  //TAKSINOMISEIES
  //Selection Sort
  auto start=high_resolution_clock::now();
  selectionSort(array_str,100);
  auto stop=high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout<<"Selection Sort:"<<duration.count()<<endl;
  //Bubble Sort
  start=high_resolution_clock::now();
  bubbleSort(array_str,100);
  stop=high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout<<"Bubble Sort:"<<duration.count()<<endl;
  //Insertion Sort
  start=high_resolution_clock::now();
  insertionSort(array_str,100);
  stop=high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout<<"Insertion Sort:"<<duration.count()<<endl;
  //Merge Sort
  start=high_resolution_clock::now();
  mergeSort(array_str,100);
  stop=high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout<<"Merge Sort:"<<duration.count()<<endl;
  //Quick Sort
  start=high_resolution_clock::now();
  quickSort(array_str,0,100-1);
  stop=high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout<<"Quick Sort:"<<duration.count()<<endl;
  //Shell Sort
  start=high_resolution_clock::now();
  shellSort(array_str,100);
  stop=high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout<<"Shell Sort:"<<duration.count()<<endl;
  //Heap Sort
  start=high_resolution_clock::now();
  heapSort(array_str,100);
  stop=high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout<<"Heap Sort:"<<duration.count()<<endl;



  return 0;
}

void swap(int *x,int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

int locOfSmallest(Structure b[],int start,int end){
    int j = start;
    for(int i=start;i<end;i++){
        if(b[i].num<b[j].num)
            j = i;
    }
    return j;
}

void selectionSort(Structure b[],int n ){
    for(int i=0;i<n;i++){
        int j = locOfSmallest(b,i,n);
        swap(&b[i].num,&b[j].num);
    }
}

void bubble(Structure b[],int n){
    for(int i=n-1;i>=0;i--){
        if(b[i].num<b[i-1].num)
            swap(&b[i].num,&b[i-1].num);
    }
}

void bubbleSort(Structure b[],int n){
    for(int i=0;i<n;i++){
        bubble(b,n);
    }
}

void insertionSort(Structure b[],int n){
    for(int i=1;i<n;i++){
        for(int j=i;j>=1;j--){
            if (b[j].num<b[j-1].num)
                swap(&b[j].num,&b[j-1].num);
            else
                break;
        }
    }
}

void mergeSort(Structure b[],int n){
    mergeSortRecursion(b,0,n-1);
}

void mergeSortRecursion(Structure b[],int l,int r){
    if (l<r){
        int m = l+(r-l)/2;
        mergeSortRecursion(b,l,m);
        mergeSortRecursion(b,m+1,r);

        mergeSortedArrays(b,l,m,r);
    }
}

void mergeSortedArrays(Structure b[],int l,int m,int r){
    int left_length = m-l+1;
    int right_length = r-m;

    int temp_left[left_length];
    int temp_right[right_length];

    int i,j,k;

    for(int i=0;i<left_length;i++)
        temp_left[i] = b[l+i].num;
    for(int i=0;i<right_length;i++)
        temp_right[i] = b[m+1+i].num;

    i=0;
    j=0;
    for(k=l;k<=r;k++){
        if ((i<left_length) && (j>=right_length || temp_left[i]<=temp_right[j])){
            b[k].num = temp_left[i];
            i++;
        }else {
            b[k].num = temp_right[j];
            j++;
    }
  }
}

void quickSort(Structure b[], int left, int right){
	int i, j, x, k;

	i = left;
	j = right;
	k = (left+right) / 2;
	x = b[k].num;

	do {
		while (b[i].num < x)
			i++;
		while (b[j].num > x)
			j--;
		if (i <= j) {
			swap(&b[i].num, &b[j].num);
			i++;
			j--;
		}
	} while (i <= j);

	if (left < j)
		quickSort(b, left, j);
	if (i < right)
		quickSort(b, i, right);
}

void shellSort(Structure b[],int n){
    for(int gap=n/2;gap>0;gap/=2){
        for(int i=gap;i<n;i++){
            int temp = b[i].num;
            int j;
            for(j=i;j>=gap&&b[j-gap].num>temp;j-=gap)
                b[j].num=b[j-gap].num;
            b[j].num=temp;
        }
    }
}

void heapify(Structure b[], int n, int i){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && b[l].num > b[largest].num)
        largest = l;

    if (r < n && b[r].num > b[largest].num)
      largest = r;

    if (largest != i) {
        swap(&b[i].num, &b[largest].num);
        heapify(b, n, largest);
    }
}

void heapSort(Structure b[], int n){
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(b, n, i);
    for (int i = n - 1; i >= 0; i--){
        swap(&b[0].num, &b[i].num);
        heapify(b, i, 0);
    }
  }
