#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <istream>
using namespace std;

int countcolumn(){  // finding column count function
	
	FILE* fp;
    int countLines = 1;
    int i;
    fp = fopen("value.txt", "r");
    if (fp == NULL)
    {
        printf("Couldn't  open the file (Could be a permission problem. Try running this as administrator)");
        fclose(fp);
        return 1;
    }
    else
    {
        while((i=fgetc(fp))!=EOF)
        {
            if (i == '\n')
                countLines++;
        }

        cout<<"Found Count: "<<countLines-1<<endl;
        
        string again;
        cout<<"Wanna continue searching(Y/N)";
        cin>>again;
        if(again=="Y"||again=="y"){
        	
        	return 1;
        	
        	
		}
		
		else{
			
			return 0;
		}
        
    }
	
}

int main()
{
	int number_of_lines = 0;
	SetConsoleTitleA("Memory scanner");
    DWORD baseAddress = 0x004000; // Base address
    int foundcount = 0;
    DWORD pid;
    HWND hwnd;

    hwnd = FindWindow(NULL,"AssaultCube"); // Window name of the program you want to scan it's memory
    if(!hwnd)// Check if the given window name found
    {
        cout <<"Couldn't find the program!";
        cin.get();
    }
    else
    {
        GetWindowThreadProcessId(hwnd,&pid);
        HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS,0,pid);// all_access means we are getting permission for read write execute
        if(!phandle)// Check the handle 
        {
            cout <<"Couldn't get handle"<<endl;
           system("pause");
        }
        else
        {
            int deger;
            int flag = 1;
            int flag2 = 1;
           	int find;
           	int find2;
           	int art = 0;
            DWORD findit = baseAddress;
            
            
            cout<<"What value you want to find(4byte): ";
            cin>>find;
            cout<<"Scanning memory.. "<<endl;
             ofstream dosyaYaz("value.txt");
             int foundcnt = 0;
             int newdeger;
			int findvalue1;
			DWORD array2[400000];
			DWORD array[2000];
			
			while(1){
				
			
				
             ReadProcessMemory(phandle,(LPCVOID)findit, &array, sizeof(array), 0); 
                
                for(int i=0;i<=sizeof(array)/4;i++){
                	
                	if(find==array[i]){
                		
                		dosyaYaz<<std::hex<<findit+4*i<<"\t"<<std::dec<<array[i]<<endl;
    
                		array2[foundcnt] = findit+4*i;
                	
						foundcnt++;
					}
					
					
					
                	
                
				}
				

				
				findit += 8000;
                
               if(findit>4294867295){
			  
               break;
            	 }
            
            	
            	}
            deger = countcolumn();
            
            int newflag = 0;
            if(deger==1){
            	
            	cout<<"Enter a new value: ";
            	cin>>find2;
            	cout<<endl;
            	
			}
            
            while(deger==1){
            	
            		 flag++;
            		 int value;
            		 for(int i=0;i<foundcnt;i++){
            		 	
            		 	ReadProcessMemory(phandle,(LPVOID)array2[i], &findvalue1, sizeof(findvalue1), NULL); 
            		 	
            		 	if(findvalue1==find2){
            		 	
            		 		dosyaYaz<<std::hex<<array2[i]<<"\t"<<std::dec<<findvalue1<<"\t"<<flag<<"'Th scan"<<endl;
            		 		findvalue1 = 0;
            		 		array2[newflag] = array2[i];
            		 		newflag++;
            		 		
						 }
            		 	
					 }
					 foundcnt = newflag;
					 	
					 string confirm;
            		cout<<"Founds: "<<newflag<<" "<<"Wanna continue scanning?(Y/N) ";
            		cin>>confirm;
            		if(confirm=="Y"||confirm=="y"){
            			
            			newflag = 0;
                	cout<<"Enter a new value: ";
                    cin>>find2;
            	    cout<<endl;
					}
					
					else{
						
					break;
					}
            		
			}
			
			string confirm;
			cout<<"Wanna write a value?(Y/N)";
					 cin>>confirm;
					 if(confirm=="Y"||confirm=="y"){
					 	
					 	DWORD towrite;
					 	int towritevalue;
					 	cout<<"Enter a memory address (without 0x): ";
					 	  std::cin >> std::hex >> towrite;
					 	  cout<<"enter a 4byte you want to write: ";
					 	  cin>>std::dec>>towritevalue;
					 	  WriteProcessMemory(phandle, (LPVOID)towrite, &towritevalue, sizeof(towritevalue), 0);
					 	  
					 }
			
			}
            
            system("pause");
        }
    }
