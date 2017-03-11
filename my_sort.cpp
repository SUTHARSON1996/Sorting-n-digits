/*		

	------------------------------------------------------------------------DOCUMENTATION-----------------------------------------------------------------

	This is a program to sort the numbers in ascending order which are present in files a.txt, b.txt, c.txt, d.txt, e.txt which can be of any no of digits
	The Logic goes as follows
		1>First we find out the no of digits in each file using tellg() function after seeking to the end of the file using seekg()
		2>Since the number of digits in each file varies, a function named primary sorting is implemented, which sorts the files based on the number of digits in the files
		3>After grouping the set of files which have the same no of digits, a function named secondary sorting is implemented to arrange this set of files alone in ascending order. This sorting compares the digits from LSB to MSB in each file of this set
		4>The resultant sorted order of the files is written to output.txt	


	----------------------------------------------------------------------END OF DOCUMENTATION-----------------------------------------------------------------

	
*/



#include<iostream>
#include<fstream>

using namespace std;

class My_sort{

	private:
		
		//input file stream array for files a.txt, b.txt, c.txt, d.txt, e.txt respectively
		ifstream file[5];
		
		//no of digits in file a.txt,b.txt,c.txt,d.txt,e.txt respectively
		int noOfDigits[5];

		//this is a matrix which gives groups the numbers that have the same no of digits
		int sameNoOFDigits[5][5];
		
		//sorted order of files in accordance with the numbers present in it
		int result[5];	

		
		
		
	
	public :

		
	
		//constructor
		My_sort(){
			file[0].open("a.txt");
			file[1].open("b.txt");
			file[2].open("c.txt");
			file[3].open("d.txt");
			file[4].open("e.txt");
		
			//result array 
			result[0]=0;
			result[1]=1;
			result[2]=2;
			result[3]=3;
			result[4]=4;
			
			//initilizing with -1
			for(int i=0;i<5;i++){
				for(int j=0;j<5;j++){
					sameNoOFDigits[i][j]=-1;
				}
				
			}


		}


		//find no of digits present in files a.txt, b.txt, c.txt, d.txt, e.txt
		int findNoOfDigits(){

			for(int i=0;i<5;i++){
				streampos begin, end;
				if(file[i].is_open()){
					begin = file[i].tellg();
					file[i].seekg(0,ios::end);
					end = file[i].tellg();
					noOfDigits[i] = (int)end-begin-1;

				}else{
					cout<<"error";
				}

			}
		}

		
		//sort the files with respect to no of digits
		void myPrimarySort(){		
			int pos,t;
			for(int i=0;i<5;i++){
				pos = i;				
				for(int j=i+1;j<5;j++){
					if(noOfDigits[j] < noOfDigits[pos]){
						pos = j;
					}
				}
				t = result[pos];
				result[pos] = result[i];
				result[i] = t;
				t = noOfDigits[pos];
				noOfDigits[pos] = noOfDigits[i];
				noOfDigits[i] = t;
					
			}
		}


		//finding the numbers which have the same number of digits
		void findSameDigitsSet(){
			int row=0,col=0;
			for(int i=0;i<4;i++){
				if(noOfDigits[i] == noOfDigits[i+1]){
					sameNoOFDigits[row][col] = i;
					col++;
				}else{
					sameNoOFDigits[row][col]=i;
					row++;
					col=0;	
				}
			}
			if(noOfDigits[4]==noOfDigits[3]){
				sameNoOFDigits[row][col]=4;
			}else{
				
				sameNoOFDigits[row][0]=4;
			}
			
			for(int i=0;i<5;i++){
				col=0;
				for(int j=0;j<5 && sameNoOFDigits[i][j]!=-1;j++){
					col++;
				}
				if(col>1){
					mySecondarySort(sameNoOFDigits[i],col);
				}
				
			}
			
			

		}



		//this sorts the numbers which have same number of digits
		void mySecondarySort(int s[5],int col){
			int num[col];
			char temp[col];
			int temp1;
			int pos,a,b;
			
			for(int i=noOfDigits[s[0]]-1;i>=0;i--){
				for(int j=0;j<col;j++){
					file[result[s[j]]].seekg(i,ios::beg);
					file[result[s[j]]].get(temp[j]);
					
				}
				

				for(a=1;a<col;a++){
					b=a;
					while(b>0 && temp[b-1]>temp[b]){
						temp1 = result[s[b]];
						result[s[b]] = result[s[b-1]];
						result[s[b-1]] = temp1;

						temp1 = temp[b];
						temp[b] = temp[b-1];
						temp[b-1] = temp1;
						b=b-1;
					}


				}

				
			}
		}

		//printing the final output
		void printSortedOrder(){
			ofstream of("output.txt");
			
			for(int i=0;i<5;i++){

				switch(result[i]){
					case 0:
						of<<"a.txt"<<"\n";		
						break;
					case 1:
						of<<"b.txt"<<"\n";		
						break;
					case 2:
						of<<"c.txt"<<"\n";		
						break;
					case 3:
						of<<"d.txt"<<"\n";		
						break;
					case 4:
						of<<"e.txt"<<"\n";		
						break;

					
				}
			}
		}

		
		//destructor
		~My_sort(){
			file[0].close();
			file[1].close();
			file[2].close();
			file[3].close();
			file[4].close();
		}


};






int main(){
	streampos begin,end;
	My_sort my_sort;
	my_sort.findNoOfDigits();
	my_sort.myPrimarySort();
	my_sort.findSameDigitsSet();
	my_sort.printSortedOrder();
	
	
	
	return 0;
}
