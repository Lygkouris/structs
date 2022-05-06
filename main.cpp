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

void swap(int *x,int *y);
int str_locOfSmallest(Structure b[],int s,int e);
void str_selectionSort(Structure b[],int n);
void str_bubble(Structure b[],int n);
void str_bubbleSort(Structure b[],int n);
void str_insertionSort(Structure b[],int n);
void str_mergeSort(Structure b[],int n );
void str_mergeSortRecursion(Structure b[],int l,int r);
void str_mergeSortedArrays(Structure b[],int l,int m,int r);
void str_quickSort(Structure b[],int left,int right);
void str_shellSort(Structure b[],int n);
void str_heapify(Structure b[], int n, int i);
void str_heapSort(Structure b[], int n);

int main(){
  Structure array_str[100];
  //perasma tyxaiwn dedomenwn apo to file sto pinaka array_str
  fstream rand_data;
  rand_data.open("rand_data.csv",ios::in);
  //dhmiourgia object gia kathe xwra kai apo8hkeysei tou sto pinaka countries[199]
	vector<string> row2;
	for(int i=0;i<100;i++){
		row2.clear();
		//h katalhksh .clear() katharizei to vector
		string line2,word2;
		getline(rand_data,line2);
		stringstream s2(line2);
		while (getline(s2,word2,','))
			row2.push_back(word2);
    //to vector apo8hkeyei string data,ara to row[0] pou periexei ton akeraio arithmo prepei na metatrapei apo string se int
    int a=stoi(row2[0]);
		array_str[i]=Structure(a,row2[1],row2[2],row2[3]);
	}

  //TAKSINOMISEIES
  //Selection Sort
  auto start=high_resolution_clock::now();
  str_selectionSort(array_str,100);
  auto stop=high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout<<"Selection Sort:"<<duration.count()<<endl;
  //Bubble Sort
  start=high_resolution_clock::now();
  str_bubbleSort(array_str,100);
  stop=high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout<<"Bubble Sort:"<<duration.count()<<endl;
  //Insertion Sort
  start=high_resolution_clock::now();
  str_insertionSort(array_str,100);
  stop=high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout<<"Insertion Sort:"<<duration.count()<<endl;
  //Merge Sort
  start=high_resolution_clock::now();
  str_mergeSort(array_str,100);
  stop=high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout<<"Merge Sort:"<<duration.count()<<endl;
  //Quick Sort
  start=high_resolution_clock::now();
  str_quickSort(array_str,0,100-1);
  stop=high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout<<"Quick Sort:"<<duration.count()<<endl;
  //Shell Sort
  start=high_resolution_clock::now();
  str_shellSort(array_str,100);
  stop=high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout<<"Shell Sort:"<<duration.count()<<endl;
  //Heap Sort
  start=high_resolution_clock::now();
  str_heapSort(array_str,100);
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

int str_locOfSmallest(Structure b[],int start,int end){
    int j = start;
    for(int i=start;i<end;i++){
        if(b[i].num<b[j].num)
            j = i;
    }
    return j;
}

void str_selectionSort(Structure b[],int n ){
    for(int i=0;i<n;i++){
        int j = str_locOfSmallest(b,i,n);
        swap(&b[i].num,&b[j].num);
    }
}

void str_bubble(Structure b[],int n){
    for(int i=n-1;i>=0;i--){
        if(b[i].num<b[i-1].num)
            swap(&b[i].num,&b[i-1].num);
    }
}

void str_bubbleSort(Structure b[],int n){
    for(int i=0;i<n;i++){
        str_bubble(b,n);
    }
}

void str_insertionSort(Structure b[],int n){
    for(int i=1;i<n;i++){
        for(int j=i;j>=1;j--){
            if (b[j].num<b[j-1].num)
                swap(&b[j].num,&b[j-1].num);
            else
                break;
        }
    }
}

void str_mergeSort(Structure b[],int n){
    str_mergeSortRecursion(b,0,n-1);
}

void str_mergeSortRecursion(Structure b[],int l,int r){
    if (l<r){
        int m = l+(r-l)/2;
        str_mergeSortRecursion(b,l,m);
        str_mergeSortRecursion(b,m+1,r);

        str_mergeSortedArrays(b,l,m,r);
    }
}

void str_mergeSortedArrays(Structure b[],int l,int m,int r){
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

void str_quickSort(Structure b[], int left, int right){
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
		str_quickSort(b, left, j);
	if (i < right)
		str_quickSort(b, i, right);
}

void str_shellSort(Structure b[],int n){
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

void str_heapify(Structure b[], int n, int i){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && b[l].num > b[largest].num)
        largest = l;

    if (r < n && b[r].num > b[largest].num)
      largest = r;

    if (largest != i) {
        swap(&b[i].num, &b[largest].num);
        str_heapify(b, n, largest);
    }
}

void str_heapSort(Structure b[], int n){
    for (int i = n / 2 - 1; i >= 0; i--)
        str_heapify(b, n, i);
    for (int i = n - 1; i >= 0; i--){
        swap(&b[0].num, &b[i].num);
        str_heapify(b, i, 0);
    }
  }
