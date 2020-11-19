#include <iostream> // cout, endl
#include <fstream> // open, is_open
#include <string> // string
#include <sstream>
#include <cstring>
#include <vector> // vector
#include <cstdlib> // atoi, system
#include <iomanip> // setw
#include <ctime> // clock, CLOCKS_PER_SEC
#define PAGE_SIZE 30 // number of output per page


using namespace std; // standard naming space

typedef struct gnode {
	
	int ID;
	int CPUBurst;
	int ArrivalTime ; 
	int Priority ; 
	bool CPU ; // using cpu now? / have used cpu?

} GNODE;


typedef struct smallStruct {
	
	int Process;
	int WaitingTime;      // waiting time = turnaround time - cpu burst ;
	int TurnaroundTime ;  // TurnaroundTime = finish time - arrival time ; 
	int FinishTime ; 
	bool Cpu ; 

} ;

typedef struct ressssult {
	
	vector<char> GanttChart;
    vector<smallStruct> allData ;  // Processes should be sorted in this

} RESSSULT;

vector<gnode> cSet ; // save all token
ressssult fcfsR ; 
ressssult nsjfR ; 
ressssult psjfR ;
ressssult ppR ;
int methodd ; 
int timeSlice ; 

char Changeee( int inn ) {
	if( inn == 0 ){
		return '0' ; 
	} //if
	else if( inn == 1 ) {
		return '1' ; 
	} // else if
	else if( inn == 2) {
		return '2' ; 
	} // else if
	else if( inn == 3) {
		return '3' ; 
	} // else if
	else if( inn == 4) {
		return '4' ; 
	} // else if
	else if( inn == 5) {
		return '5' ; 
	} // else if
	else if( inn == 6) {
		return '6' ; 
	} // else if
	else if( inn == 7) {
		return '7' ; 
	} // else if
	else if( inn == 8) {
		return '8' ; 
	} // else if
	else if( inn == 9) {
		return '9' ; 
	} // else if
	else if( inn == 10) {
		return 'A' ; 
	} // else if
	else if( inn == 11) {
		return 'B' ; 
	} // else if
	else if( inn == 12) {
		return 'C' ; 
	} // else if
	else if( inn == 13) {
		return 'D' ; 
	} // else if
	else if( inn == 14) {
		return 'E' ; 
	} // else if
	else if( inn == 15) {
		return 'F' ; 
	} // else if
	else if( inn == 16) {
		return 'G' ; 
	} // else if
	else if( inn == 17) {
		return 'H' ; 
	} // else if
	else if( inn == 18) {
		return 'I' ; 
	} // else if
	else if( inn == 19) {
		return 'J' ; 
	} // else if
	else if( inn == 20) {
		return 'K' ; 
	} // else if
	else if( inn == 21) {
		return 'L' ; 
	} // else if
	else if( inn == 22) {
		return 'M' ; 
	} // else if
	else if( inn == 23) {
		return 'N' ; 
	} // else if
	else if( inn == 24) {
		return 'O' ; 
	} // else if
	else if( inn == 25) {
		return 'P' ; 
	} // else if
	else if( inn == 26) {
		return 'Q' ; 
	} // else if
	else if( inn == 27) {
		return 'R' ; 
	} // else if
	else if( inn == 28) {
		return 'S' ; 
	} // else if
	else if( inn == 29) {
		return 'T' ; 
	} // else if
	else if( inn == 30) {
		return 'U' ; 
	} // else if
	else if( inn == 31) {
		return 'V' ; 
	} // else if
	else if( inn == 32) {
		return 'W' ; 
	} // else if
	else if( inn == 33) {
		return 'X' ; 
	} // else if
	else if( inn == 34) {
		return 'Y' ; 
	} // else if
	else if( inn == 35) {
		return 'Z' ; 
	} // else if
	else {
		return '-' ; // error
	} // else
} // Changeee
//-------------------------------------------------

void ReadAll() {
	fstream inFile;
	string fileName ; 
	cout << " Input a file name : " ; 
	cin >> fileName ; 
	fileName = fileName + ".txt" ; 
	string temp ; 
	string token;
	
	
	inFile.open(fileName.c_str(), fstream::in);   // open file to read
	if (!inFile.is_open()) {                        // unable to open file
        cout << endl << "### " << fileName << " does not exist! ###" << endl;
        exit(0) ;
    } // if
    else {
    	getline(inFile, temp) ; 
    	istringstream lineStream2(temp);
    	lineStream2 >> temp ; 
    	methodd = stoi(temp) ; 
        lineStream2 >> temp ; 
        timeSlice = stoi(temp) ;
//        cout << methodd << " " << timeSlice << endl ; 
//        exit(0) ;
		int count = 0 ;
        bool first = true ; 
        while (first)   // get each input record line by line
        { 
          if(getline(inFile, temp) ) {
          	count = 0 ;
          	istringstream lineStream(temp);
          	gnode oneS ;
            while(lineStream >> temp) {
//          	   cout << temp << endl ; 
          	   if( strcmpi("ID", temp.c_str()) == 0 ) {
          	 	  oneS.ID = count ; 
			   } // if 
			   else if ( strcmpi("CPU", temp.c_str()) == 0 ) {
			   	   lineStream >> temp ; // Burst
//			   	   cout << temp << endl ;
			   	   oneS.CPUBurst = count ;  
			   } // else if
			   else if ( strcmpi("Arrival", temp.c_str()) == 0 ) {
			   	    lineStream >> temp ; // Time
			   	    oneS.ArrivalTime = count ;
			   } // else if
			   else if ( strcmpi("Priority", temp.c_str()) == 0 ) {
			   	    oneS.Priority = count ;
			   } // else if
			   
			   count ++ ;
            } // while
            
            cSet.push_back(oneS) ;
		  } // if 
		  else {
		  	cout << "### Nothing to read ! ###" << endl ; 
		  	inFile.close(); 
		  	exit(0) ;
		  } // else 
          first = false ; 
        } // while
        
        count = 0 ; 
        
        while (getline(inFile, temp))   // get each input record line by line
        { 
          count = 0 ;
          istringstream lineStream(temp);
          gnode oneS ; 
          while(lineStream >> temp) {
//          	 cout << temp << endl ; 
          	 if( cSet.at(0).ID == count ) {
          	 	oneS.ID = stoi(temp) ; 
			   } // if 
			   else if( cSet.at(0).CPUBurst == count ) {
			   	oneS.CPUBurst = stoi(temp) ;
			   } // else if 
			   else if( cSet.at(0).ArrivalTime == count ) {
			   	oneS.ArrivalTime = stoi(temp) ;
			   } // else if
			   else if ( cSet.at(0).Priority == count ) {
			   	oneS.Priority = stoi(temp) ;
			   } // else if
			   else {
			   	cout << "Weird input !" << endl ;
			   } // else

               count ++ ;
          } // while
          
          oneS.CPU = false ; 
          cSet.push_back(oneS) ;
          
        } // while
    } // else
    
    cSet.erase(cSet.begin()); // i used it to check the input 順序 
    inFile.close();
} // ReadAll

//-------------------------------------------------

void BubbleSort () {   // Sort by Id

   for (int i = cSet.size() - 1; i > 0; --i) {
        for (int j = 0; j < i; ++j){
        	if (cSet.at(j).ID > cSet.at(j+1).ID) {
        		swap( cSet.at(j), cSet.at(j+1) ) ;
//        		gnode oneS ; 
//        		oneS.ID = cSet.at(j+1).ID ; 
//        		oneS.CPUBurst = cSet.at(j+1).CPUBurst ; 
//        		oneS.ArrivalTime = cSet.at(j+1).ArrivalTime ; 
//        		oneS.Priority = cSet.at(j+1).Priority ;
//        		
//        		cSet.at(j+1).ID = cSet.at(j).ID ; 
//        		cSet.at(j+1).CPUBurst = cSet.at(j).CPUBurst ;
//        		cSet.at(j+1).ArrivalTime = cSet.at(j).ArrivalTime ;
//        		cSet.at(j+1).Priority = cSet.at(j).Priority ;
//        		
//        		cSet.at(j).ID = oneS.ID ; 
//        		cSet.at(j).CPUBurst = oneS.CPUBurst ; 
//        		cSet.at(j).ArrivalTime = oneS.ArrivalTime ; 
//        		cSet.at(j).Priority = oneS.Priority ; 
			} // if
                
		} // for
            
   } // for 
} // BubbleSort
//-------------------------------------------------
void FCFS() {
	fcfsR.allData.clear() ; 
	fcfsR.GanttChart.clear() ;
	vector<gnode> new_Vector ;
	new_Vector.assign(cSet.begin(), cSet.end());
	
	for (int i = new_Vector.size() - 1; i > 0; --i) {   // bubble sort by ArrivalTime
        for (int j = 0; j < i; ++j){
        	if (new_Vector.at(j).ArrivalTime > new_Vector.at(j+1).ArrivalTime) {
        		swap( new_Vector.at(j), new_Vector.at(j+1) ) ;
			} // if
			else if ( new_Vector.at(j).ArrivalTime == new_Vector.at(j+1).ArrivalTime ) {
				if (new_Vector.at(j).ID > new_Vector.at(j+1).ID) {
        			
			    } // if
			} // else if
                
		} // for
            
   } // for 
   
   
   int timee = 0 ; 
   
   for ( int v = 0 ; new_Vector.size() != 0 && v < new_Vector.size() ; v++ ) {
   	 int burst = new_Vector.at(v).CPUBurst ; 
   	 for ( ; new_Vector.at(v).CPUBurst > 0 ; ) {
   	 	if( new_Vector.at(v).ArrivalTime <= timee ) {
   	 		fcfsR.GanttChart.push_back( Changeee(new_Vector.at(v).ID) ) ;
   	 		new_Vector.at(v).CPUBurst = new_Vector.at(v).CPUBurst - 1 ;
		} // if
		
		timee++ ;
	 } // for
	 
	 smallStruct oneD ;
	 oneD.Process = new_Vector.at(v).ID ; 
	 oneD.FinishTime = timee ; 
	 oneD.TurnaroundTime = timee - new_Vector.at(v).ArrivalTime ; 
	 oneD.WaitingTime = oneD.TurnaroundTime - burst ; 
	 
	 fcfsR.allData.push_back(oneD) ;
   } // for 
	
	
} // FCFS

//------------------------------------------------

void NSJF() {                             // 要用一個waiting queue 因為考量抵達時間過早 又要最短工作優先 
	nsjfR.allData.clear() ;               // 像P9跟P2都在第一秒到，P9卻要等到後面做 
	nsjfR.GanttChart.clear() ;
	vector<gnode> new_Vector ;
	new_Vector.assign(cSet.begin(), cSet.end());
	
	for (int i = new_Vector.size() - 1; i > 0; --i) {   // bubble sort 
        for (int j = 0; j < i; ++j) {
        	if (new_Vector.at(j).ArrivalTime > new_Vector.at(j+1).ArrivalTime) {
        		swap( new_Vector.at(j), new_Vector.at(j+1) ) ; 
			} // if
			else if ( new_Vector.at(j).ArrivalTime == new_Vector.at(j+1).ArrivalTime ) {
				if (new_Vector.at(j).CPUBurst > new_Vector.at(j+1).CPUBurst) {
        			swap( new_Vector.at(j), new_Vector.at(j+1) ) ;
			    } // if
			    else if ( new_Vector.at(j).CPUBurst == new_Vector.at(j+1).CPUBurst ) {
			    	if (new_Vector.at(j).ID > new_Vector.at(j+1).ID) {
			    		swap( new_Vector.at(j), new_Vector.at(j+1) ) ;
        			} // if
				} // else if 
			} // else if
                
		} // for
            
   } // for 
   
//   exit(0);
//   for( int a = 0 ; a < new_Vector.size() ; a++ ) {
//	cout << new_Vector.at(a).ID << endl ; 
//   } // for test all token
   
   vector<gnode> waitingQueue ;
   waitingQueue.clear() ; 
//   cout << "test" << endl ;  // test
//   exit(0) ; // test
   int timee = 0 ; 
   bool cpuUsing = false ; 
   
   for ( ; (new_Vector.size() + waitingQueue.size()) > 0 ; ) {
//   	cout << new_Vector.at(0).ID << endl ; //test
//   	system("pause") ; //test
   	 if( cpuUsing == false && waitingQueue.size() != 0 ) {
   	 	if( (new_Vector.size() != 0 && waitingQueue.at(0).CPUBurst < new_Vector.at(0).CPUBurst) || new_Vector.size() == 0 ||
			(new_Vector.size() != 0 && new_Vector.at(0).ArrivalTime > timee) ||
			(new_Vector.size() != 0 && waitingQueue.at(0).CPUBurst == new_Vector.at(0).CPUBurst &&
			 waitingQueue.at(0).ArrivalTime < new_Vector.at(0).ArrivalTime) ) {
   	 		new_Vector.insert( new_Vector.begin(), waitingQueue.at(0) ) ; 
//   	 		cout << new_Vector.at(0).ID << endl ; 
   	 		cpuUsing = true ;
   	 		waitingQueue.erase( waitingQueue.begin() ) ;
		} // if
		else {
			cpuUsing = true ;
		} // else
		
		for ( int b = 1 ; b < new_Vector.size() ; b++ ) {
		    		if ( new_Vector.at(b).ArrivalTime <= timee ) { // get in waiting queue
						waitingQueue.push_back( new_Vector.at(b) ) ;
						new_Vector.erase( new_Vector.begin() + b ) ; 
					} // if 
		} // for
		
		for (int i = waitingQueue.size() - 1; i > 0; --i) {   // bubble sort 
        	for (int j = 0; j < i; ++j) {
      			if (waitingQueue.at(j).CPUBurst > waitingQueue.at(j+1).CPUBurst) {
        			swap( waitingQueue.at(j), waitingQueue.at(j+1) ) ; 
				} // if
				else if ( waitingQueue.at(j).CPUBurst == waitingQueue.at(j+1).CPUBurst ) {
					if (waitingQueue.at(j).ArrivalTime > waitingQueue.at(j+1).ArrivalTime) {
        				swap( waitingQueue.at(j), waitingQueue.at(j+1) ) ;
			    	} // if
			    	else if ( waitingQueue.at(j).ArrivalTime == waitingQueue.at(j+1).ArrivalTime ) {
			    		if (waitingQueue.at(j).ID > waitingQueue.at(j+1).ID) {
			    			swap( waitingQueue.at(j), waitingQueue.at(j+1) ) ;
        				} // if
					} // else if 
				} // else if
			} // for
   		} // for
		
//		cout << new_Vector.size() << "..." << endl ; // test
	 } // if
   	 else if( cpuUsing == false && waitingQueue.size() == 0 ) {
   	 	int po = 1 ; 
//   	 	bool first = true ; //test
   	 	if( new_Vector.at(0).ArrivalTime <= timee ) { // get one in cpu
   				cpuUsing = true ;
   				for ( po = 1 ; po < new_Vector.size() ; po++ ) {
		    		if ( new_Vector.at(po).ArrivalTime <= timee ) { // get in waiting queue
						waitingQueue.push_back( new_Vector.at(po) ) ;
						new_Vector.erase( new_Vector.begin() + po ) ; 
					} // if 
		        } // for  
		} // if 
		else {
			timee ++ ; 
		} // else 
		
		for (int i = waitingQueue.size() - 1; i > 0; --i) {   // bubble sort 
        	for (int j = 0; j < i; ++j) {
      			if (waitingQueue.at(j).CPUBurst > waitingQueue.at(j+1).CPUBurst) {
        			swap( waitingQueue.at(j), waitingQueue.at(j+1) ) ; 
				} // if
				else if ( waitingQueue.at(j).CPUBurst == waitingQueue.at(j+1).CPUBurst ) {
					if (waitingQueue.at(j).ArrivalTime > waitingQueue.at(j+1).ArrivalTime) {
        				swap( waitingQueue.at(j), waitingQueue.at(j+1) ) ;
			    	} // if
			    	else if ( waitingQueue.at(j).ArrivalTime == waitingQueue.at(j+1).ArrivalTime ) {
			    		if (waitingQueue.at(j).ID > waitingQueue.at(j+1).ID) {
			    			swap( waitingQueue.at(j), waitingQueue.at(j+1) ) ;
        				} // if
					} // else if 
				} // else if
			} // for
   		} // for
		
//		cout << new_Vector.size() << "+++" << endl ; // test
	 } // else if
	 else {
	 	int burst = new_Vector.at(0).CPUBurst ; 
	 	for ( ; new_Vector.at(0).CPUBurst > 0 ; ) {
   	 		nsjfR.GanttChart.push_back( Changeee(new_Vector.at(0).ID) ) ;
   	 		new_Vector.at(0).CPUBurst = new_Vector.at(0).CPUBurst -1 ; 
//   	 		cout << new_Vector.at(0).CPUBurst << endl ; // test
			timee++ ;
	 	} // for
	 	
	 	int po =1 ; 
	 	 for ( po = 1 ; po < new_Vector.size() ; po++ ) {
		    		if ( new_Vector.at(po).ArrivalTime <= timee ) { // get in waiting queue
						waitingQueue.push_back( new_Vector.at(po) ) ;
						new_Vector.erase( new_Vector.begin() + po ) ; 
					} // if 
		} // for 
	 	
	 	 smallStruct oneD ;
		 oneD.Process = new_Vector.at(0).ID ; 
		 oneD.FinishTime = timee ; 
		 oneD.TurnaroundTime = timee - new_Vector.at(0).ArrivalTime ; 
		 oneD.WaitingTime = oneD.TurnaroundTime - burst ; 
	 
		 nsjfR.allData.push_back(oneD) ;
		 
		 new_Vector.erase(new_Vector.begin()) ;
	 	 cpuUsing = false ; 

	 } // else

	 
   } // for 
	
	
} // NSJF

//------------------------------------------------

void Bubble4PSJF( vector<gnode> &nVector ) {
	for (int i = nVector.size() - 1; i > 0; --i) {   // bubble sort by CPUBurst
        for (int j = 0; j < i; ++j){
        	if (nVector.at(j).CPUBurst > nVector.at(j+1).CPUBurst) {
//        		nVector.at(j).CPU = false ; 
        		swap( nVector.at(j), nVector.at(j+1) ) ;
			} // if
			else if ( nVector.at(j).CPUBurst == nVector.at(j+1).CPUBurst ) {
				if( nVector.at(j).CPU == true && nVector.at(j+1).CPU == false ){
					swap( nVector.at(j), nVector.at(j+1) ) ;
				} // if
				else if( nVector.at(j).CPU == false && nVector.at(j+1).CPU == true ) {
//					swap( nVector.at(j), nVector.at(j+1) ) ;
//					nVector.at(j).CPU = false ; 
				} // else if
				else if (nVector.at(j).ArrivalTime > nVector.at(j+1).ArrivalTime) {
        			swap( nVector.at(j), nVector.at(j+1) ) ;
			    } // else if
			    else if ( nVector.at(j).ArrivalTime == nVector.at(j+1).ArrivalTime ) {
			    	if (nVector.at(j).ID > nVector.at(j+1).ID) {
			    		swap( nVector.at(j), nVector.at(j+1) ) ;
        			} // if
				} // else if 
			} // else if
                
		} // for
            
   } // for
}// Bubble4PSJF

void PSJF() {
	psjfR.allData.clear() ; 
	psjfR.GanttChart.clear() ;
	vector<gnode> new_Vector ;
	new_Vector.assign(cSet.begin(), cSet.end());
	for (int i = new_Vector.size() - 1; i > 0; --i) {   // bubble sort 
        for (int j = 0; j < i; ++j) {
        	if (new_Vector.at(j).ArrivalTime > new_Vector.at(j+1).ArrivalTime) {
        		swap( new_Vector.at(j), new_Vector.at(j+1) ) ; 
			} // if
			else if ( new_Vector.at(j).ArrivalTime == new_Vector.at(j+1).ArrivalTime ) {
				if (new_Vector.at(j).CPUBurst > new_Vector.at(j+1).CPUBurst) {
        			swap( new_Vector.at(j), new_Vector.at(j+1) ) ;
			    } // if
			    else if ( new_Vector.at(j).CPUBurst == new_Vector.at(j+1).CPUBurst ) {
			    	if (new_Vector.at(j).ID > new_Vector.at(j+1).ID) {
			    		swap( new_Vector.at(j), new_Vector.at(j+1) ) ;
        			} // if
				} // else if 
			} // else if
                
		} // for
            
   } // for 
   
//   exit(0);
//   for( int a = 0 ; a < new_Vector.size() ; a++ ) {
//	cout << new_Vector.at(a).ID << endl ; 
//   } // for test all token
   
   vector<gnode> waitingQueue ;
   waitingQueue.clear() ; 
//   cout << "test" << endl ;  // test
//   exit(0) ; // test
   int timee = 0 ; 
   bool cpuUsing = false ; 
   
   for ( ; (new_Vector.size() + waitingQueue.size()) > 0 ; ) {
//   	cout << new_Vector.at(0).ID << endl ; //test
//   	system("pause") ; //test
   	 if( cpuUsing == false && waitingQueue.size() != 0 ) {
		if( new_Vector.size() > 1 && new_Vector.at(1).ArrivalTime <= timee && 
		    new_Vector.at(0).CPUBurst > new_Vector.at(1).CPUBurst ){
			cpuUsing = true ;
			waitingQueue.push_back( new_Vector.at(0) ) ;
			new_Vector.erase(new_Vector.begin()) ;
			int po = 1 ; 
			for ( po = 1 ; po < new_Vector.size() ; po++ ) {
		    		if ( new_Vector.at(po).ArrivalTime <= timee ) { // get in waiting queue
						waitingQueue.push_back( new_Vector.at(po) ) ;
						new_Vector.erase( new_Vector.begin() + po ) ; 
					} // if 
		    } // for  
		} // if
   	 	else if( (new_Vector.size() != 0 && waitingQueue.at(0).CPUBurst < new_Vector.at(0).CPUBurst) || new_Vector.size() == 0 ||
			(new_Vector.size() != 0 && new_Vector.at(0).ArrivalTime > timee) ||
			(new_Vector.size() != 0 && waitingQueue.at(0).CPUBurst == new_Vector.at(0).CPUBurst &&
			 waitingQueue.at(0).CPU == false && new_Vector.at(0).CPU == true ) ||
			(new_Vector.size() != 0 && waitingQueue.at(0).CPUBurst == new_Vector.at(0).CPUBurst &&
			 waitingQueue.at(0).ArrivalTime < new_Vector.at(0).ArrivalTime) ) {
//			 	cout << waitingQueue.at(0).ID << endl ; 
            if( new_Vector.size() != 0 && waitingQueue.at(0).CPUBurst == new_Vector.at(0).CPUBurst &&
			 waitingQueue.at(0).CPU == true && new_Vector.at(0).CPU == true ){  // 目前佔有CPU的不用趕下來 
            	cpuUsing = true ;
			} // if 
			else {
				new_Vector.insert( new_Vector.begin(), waitingQueue.at(0) ) ; 
//   	 		cout << new_Vector.at(0).ID << endl ; 
   	 			cpuUsing = true ;
   	 			waitingQueue.erase( waitingQueue.begin() ) ;
			} // else 
   	 		
		} //else if
		else {
			cpuUsing = true ;
		} // else
		
		for ( int b = 1 ; b < new_Vector.size() ; b++ ) {
		    		if ( new_Vector.at(b).ArrivalTime <= timee ) { // get in waiting queue
						waitingQueue.push_back( new_Vector.at(b) ) ;
						new_Vector.erase( new_Vector.begin() + b ) ; 
					} // if 
		} // for
		
		Bubble4PSJF( waitingQueue ) ; 
		
//		cout << new_Vector.size() << "..." << endl ; // test
	 } // if
   	 else if( cpuUsing == false && waitingQueue.size() == 0 ) {
   	 	int po = 1 ; 
//   	 	bool first = true ; //test
		if( new_Vector.size() > 1 && new_Vector.at(1).ArrivalTime <= timee && 
		    new_Vector.at(0).CPUBurst > new_Vector.at(1).CPUBurst ){
			cpuUsing = true ;
			waitingQueue.push_back( new_Vector.at(0) ) ;
			new_Vector.erase(new_Vector.begin()) ;
			
			for ( po = 1 ; po < new_Vector.size() ; po++ ) {
		    		if ( new_Vector.at(po).ArrivalTime <= timee ) { // get in waiting queue
						waitingQueue.push_back( new_Vector.at(po) ) ;
						new_Vector.erase( new_Vector.begin() + po ) ; 
					} // if 
		    } // for  
		} // if
   	 	else if( new_Vector.at(0).ArrivalTime <= timee ) { // get one in cpu
   				cpuUsing = true ;
   				for ( po = 1 ; po < new_Vector.size() ; po++ ) {
		    		if ( new_Vector.at(po).ArrivalTime <= timee ) { // get in waiting queue
						waitingQueue.push_back( new_Vector.at(po) ) ;
						new_Vector.erase( new_Vector.begin() + po ) ; 
					} // if 
		        } // for  
		} //else if 
		else {
			timee ++ ; 
		} // else 
		
		Bubble4PSJF( waitingQueue ) ; 
		
//		cout << new_Vector.size() << "+++" << endl ; // test
	 } // else if
	 else {
	 	int burst = new_Vector.at(0).CPUBurst ; 
	 	new_Vector.at(0).CPU = true ; 
	 	int sllice = timeSlice ; 
	 	for ( ; sllice > 0 && new_Vector.at(0).CPUBurst > 0 ; ) {
   	 		psjfR.GanttChart.push_back( Changeee(new_Vector.at(0).ID) ) ;
   	 		new_Vector.at(0).CPUBurst = new_Vector.at(0).CPUBurst -1 ; 
//   	 		cout << new_Vector.at(0).CPUBurst << endl ; // test
			timee++ ;
			sllice = sllice - 1 ; 
			
	 	} // for
	 	
	 	if( new_Vector.at(0).CPUBurst == 0 ) { // finish
		  smallStruct oneD ;
		  oneD.Process = new_Vector.at(0).ID ; 
		  oneD.FinishTime = timee ; 
		  oneD.TurnaroundTime = timee - new_Vector.at(0).ArrivalTime ; 
//		  oneD.WaitingTime = oneD.TurnaroundTime - burst ; /// !!!!!!!! 要另外算 

		  psjfR.allData.push_back(oneD) ;
		  new_Vector.erase(new_Vector.begin()) ;
		} // if 
		else if( waitingQueue.size() != 0 && new_Vector.at(0).CPUBurst > waitingQueue.at(0).CPUBurst ){
			waitingQueue.push_back( new_Vector.at(0) ) ;
			new_Vector.erase(new_Vector.begin()) ;
			Bubble4PSJF( waitingQueue ) ; 
		} // else
		else if( new_Vector.size() > 1 && new_Vector.at(1).ArrivalTime <= timee && new_Vector.at(0).CPUBurst> new_Vector.at(1).CPUBurst ){
			waitingQueue.push_back( new_Vector.at(0) ) ;
			new_Vector.erase(new_Vector.begin()) ;
			Bubble4PSJF( waitingQueue ) ; 
		} // else
	 	 
	 	 int po =1 ; 
	 	 for ( po = 1 ; po < new_Vector.size() ; po++ ) {
		    		if ( new_Vector.at(po).ArrivalTime <= timee ) { // get in waiting queue
						waitingQueue.push_back( new_Vector.at(po) ) ;
						new_Vector.erase( new_Vector.begin() + po ) ; 
					} // if 
		} // for 
		
	 	 cpuUsing = false ; 

	 } // else

	 
   } // for 
} // PSJF

//--------------------------------------------------
void Bubble4PP( vector<gnode> &nVector ) {
	for (int i = nVector.size() - 1; i > 0; --i) {   // bubble sort by CPUBurst
        for (int j = 0; j < i; ++j){
        	if (nVector.at(j).Priority > nVector.at(j+1).Priority) {
        		swap( nVector.at(j), nVector.at(j+1) ) ;
			} // if
			else if ( nVector.at(j).Priority == nVector.at(j+1).Priority ) {
				if( nVector.at(j).CPU == true && nVector.at(j+1).CPU == false ){
					swap( nVector.at(j), nVector.at(j+1) ) ;
				} // if
				else if( nVector.at(j).CPU == false && nVector.at(j+1).CPU == true ) {
//					swap( nVector.at(j), nVector.at(j+1) ) ;
				} // else if
				else if (nVector.at(j).ArrivalTime > nVector.at(j+1).ArrivalTime) {
        			swap( nVector.at(j), nVector.at(j+1) ) ;
			    } // else if
			    else if ( nVector.at(j).ArrivalTime == nVector.at(j+1).ArrivalTime ) {
			    	if (nVector.at(j).ID > nVector.at(j+1).ID) {
			    		swap( nVector.at(j), nVector.at(j+1) ) ;
        			} // if
				} // else if 
			} // else if
                
		} // for
            
   } // for
}// Bubble4PP

void PP() {
	ppR.allData.clear() ; 
	ppR.GanttChart.clear() ;
	vector<gnode> new_Vector ;
	new_Vector.assign(cSet.begin(), cSet.end());
	for (int i = new_Vector.size() - 1; i > 0; --i) {   // bubble sort 
        for (int j = 0; j < i; ++j) {
        	if (new_Vector.at(j).ArrivalTime > new_Vector.at(j+1).ArrivalTime) {
        		swap( new_Vector.at(j), new_Vector.at(j+1) ) ; 
			} // if
			else if ( new_Vector.at(j).ArrivalTime == new_Vector.at(j+1).ArrivalTime ) {
				if (new_Vector.at(j).Priority > new_Vector.at(j+1).Priority) {
        			swap( new_Vector.at(j), new_Vector.at(j+1) ) ;
			    } // if
			    else if ( new_Vector.at(j).Priority == new_Vector.at(j+1).Priority ) {
			    	if (new_Vector.at(j).ID > new_Vector.at(j+1).ID) {
			    		swap( new_Vector.at(j), new_Vector.at(j+1) ) ;
        			} // if
				} // else if 
			} // else if
                
		} // for
            
   } // for 
   
//   exit(0);
//   for( int a = 0 ; a < new_Vector.size() ; a++ ) {
//	cout << new_Vector.at(a).ID << endl ; 
//   } // for test all token
   
   vector<gnode> waitingQueue ;
   waitingQueue.clear() ; 
//   cout << "test" << endl ;  // test
//   exit(0) ; // test
   int timee = 1 ; 
   bool cpuUsing = false ; 
   
   for ( ; (new_Vector.size() + waitingQueue.size()) > 0 ; ) {
//   	cout << new_Vector.at(0).ID << endl ; //test
//   	system("pause") ; //test
   	 if( cpuUsing == false && waitingQueue.size() != 0 ) {
		if( new_Vector.size() > 1 && new_Vector.at(1).ArrivalTime <= timee && 
		    new_Vector.at(0).Priority > new_Vector.at(1).Priority ){
			cpuUsing = true ;
			waitingQueue.push_back( new_Vector.at(0) ) ;
			new_Vector.erase(new_Vector.begin()) ;
			int po = 1 ; 
			for ( po = 1 ; po < new_Vector.size() ; po++ ) {
		    		if ( new_Vector.at(po).ArrivalTime <= timee ) { // get in waiting queue
						waitingQueue.push_back( new_Vector.at(po) ) ;
						new_Vector.erase( new_Vector.begin() + po ) ; 
					} // if 
		    } // for  
		} // if
   	 	else if( (new_Vector.size() != 0 && waitingQueue.at(0).Priority < new_Vector.at(0).Priority) ||
			 new_Vector.size() == 0 ||
			(new_Vector.size() != 0 && new_Vector.at(0).ArrivalTime > timee) ||
			(new_Vector.size() != 0 && waitingQueue.at(0).Priority == new_Vector.at(0).Priority &&
			 waitingQueue.at(0).CPU == false && new_Vector.at(0).CPU == true ) ||
			(new_Vector.size() != 0 && waitingQueue.at(0).Priority == new_Vector.at(0).Priority &&
			 waitingQueue.at(0).ArrivalTime < new_Vector.at(0).ArrivalTime) ) {
			 	
			if( new_Vector.size() != 0 && waitingQueue.at(0).Priority == new_Vector.at(0).Priority &&
			 waitingQueue.at(0).CPU == true && new_Vector.at(0).CPU == true ){  // 目前佔有CPU的不用趕下來 
            	cpuUsing = true ;
			} // if 
			else {
				new_Vector.insert( new_Vector.begin(), waitingQueue.at(0) ) ; 
//   	 		cout << new_Vector.at(0).ID << endl ; 
   	 			cpuUsing = true ;
   	 			waitingQueue.erase( waitingQueue.begin() ) ;
			} // else 
		} //else if
		else {
			cpuUsing = true ;
		} // else
		
		for ( int b = 1 ; b < new_Vector.size() ; b++ ) {
		    		if ( new_Vector.at(b).ArrivalTime <= timee ) { // get in waiting queue
						waitingQueue.push_back( new_Vector.at(b) ) ;
						new_Vector.erase( new_Vector.begin() + b ) ; 
					} // if 
		} // for
		
		Bubble4PP( waitingQueue ) ; 
		
//		cout << new_Vector.size() << "..." << endl ; // test
	 } // if
   	 else if( cpuUsing == false && waitingQueue.size() == 0 ) {
   	 	int po = 1 ; 
//   	 	bool first = true ; //test
		if( new_Vector.size() > 1 && new_Vector.at(1).ArrivalTime <= timee && 
		    new_Vector.at(0).Priority > new_Vector.at(1).Priority ){
			cpuUsing = true ;
			waitingQueue.push_back( new_Vector.at(0) ) ;
			new_Vector.erase(new_Vector.begin()) ;
			
			for ( po = 1 ; po < new_Vector.size() ; po++ ) {
		    		if ( new_Vector.at(po).ArrivalTime <= timee ) { // get in waiting queue
						waitingQueue.push_back( new_Vector.at(po) ) ;
						new_Vector.erase( new_Vector.begin() + po ) ; 
					} // if 
		    } // for  
		} // if
   	 	else if( new_Vector.at(0).ArrivalTime <= timee ) { // get one in cpu
   				cpuUsing = true ;
   				for ( po = 1 ; po < new_Vector.size() ; po++ ) {
		    		if ( new_Vector.at(po).ArrivalTime <= timee ) { // get in waiting queue
						waitingQueue.push_back( new_Vector.at(po) ) ;
						new_Vector.erase( new_Vector.begin() + po ) ; 
					} // if 
		        } // for  
		} //else if 
		else {
			timee ++ ; 
		} // else 
		
		Bubble4PP( waitingQueue ) ; 
		
//		cout << new_Vector.size() << "+++" << endl ; // test
	 } // else if
	 else {
	 	int burst = new_Vector.at(0).CPUBurst ; 
	 	new_Vector.at(0).CPU = true ; 
	 	int sllice = timeSlice ; 
	 	for ( ; sllice > 0 && new_Vector.at(0).CPUBurst > 0 ; ) {
   	 		ppR.GanttChart.push_back( Changeee(new_Vector.at(0).ID) ) ;
   	 		new_Vector.at(0).CPUBurst = new_Vector.at(0).CPUBurst -1 ; 
//   	 		cout << new_Vector.at(0).CPUBurst << endl ; // test
			timee++ ;
			sllice = sllice - 1 ; 
			
	 	} // for
	 	
	 	if( new_Vector.at(0).CPUBurst == 0 ) { // finish
		  smallStruct oneD ;
		  oneD.Process = new_Vector.at(0).ID ; 
		  oneD.FinishTime = timee ; 
		  oneD.TurnaroundTime = timee - new_Vector.at(0).ArrivalTime ; 
//		  oneD.WaitingTime = oneD.TurnaroundTime - burst ; /// !!!!!!!! 要另外算 

		  ppR.allData.push_back(oneD) ;
		  new_Vector.erase(new_Vector.begin()) ;
		} // if 
		else if( waitingQueue.size() != 0 && new_Vector.at(0).Priority > waitingQueue.at(0).Priority ){
			waitingQueue.push_back( new_Vector.at(0) ) ;
			new_Vector.erase(new_Vector.begin()) ;
			Bubble4PP( waitingQueue ) ; 
		} // else
	 	else if( new_Vector.size() > 1 && new_Vector.at(1).ArrivalTime <= timee && new_Vector.at(0).Priority> new_Vector.at(1).Priority ){
			waitingQueue.push_back( new_Vector.at(0) ) ;
			new_Vector.erase(new_Vector.begin()) ;
			Bubble4PSJF( waitingQueue ) ; 
		} // else
		
		int po =1 ; 
	 	 for ( po = 1 ; po < new_Vector.size() ; po++ ) {
		    		if ( new_Vector.at(po).ArrivalTime <= timee ) { // get in waiting queue
						waitingQueue.push_back( new_Vector.at(po) ) ;
						new_Vector.erase( new_Vector.begin() + po ) ; 
					} // if 
		} // for 
	 	 cpuUsing = false ; 

	 } // else

	 
   } // for 
} // PP

//---------------------------------------------------

bool writeRecords()                            
{
	
	cout << "type in output file name : " ;
	string fname ; 
	cin >>  fname ; 
    string FileName = fname  + ".txt"; // output file name
    fstream fp;
    fp.open(FileName.c_str(), fstream::out); // create a new file to write
    if(!fp){//如果開啟檔案失敗，fp為0；成功，fp為非0
        cout<<"Fail to open file: "<<fname<<endl;
        return false ;
    } // if
    else {
    	if( methodd == 1 || methodd == 6 ) { // FCFS 
    		fp << "==" << setw(8) << "FCFS" << "==" << endl << "-";
    		for( int a = 0 ; a < fcfsR.GanttChart.size() ; a++ ) {
				fp << fcfsR.GanttChart.at(a) ; 
			} // for
			fp << endl ; 
		} // if
		
		if( methodd == 4 || methodd == 6 ) { // RR 
    		fp << "==" << setw(8) << "RR" << "==" <<endl<< "-";
    		fp << endl  ; 
		} // if
		
		if( methodd == 3 || methodd == 6 ) { // PSJF 
    		fp << "==" << setw(8) << "PSJF" << "==" <<endl<< "-";
    		for( int a = 0 ; a < psjfR.GanttChart.size() ; a++ ) {
				fp << psjfR.GanttChart.at(a) ; 
			} // for
			fp << endl ; 
		} // if
		
		if( methodd == 2 || methodd == 6 ) { // NSJF 
    		fp << "==" << setw(8) << "Non-PSJF" << "==" <<endl<< "-";
    		for( int a = 0 ; a < nsjfR.GanttChart.size() ; a++ ) {
				fp << nsjfR.GanttChart.at(a) ; 
			} // for
			fp << endl ; 
		} // if
		
		if( methodd == 5 || methodd == 6 ) { // PP
    		fp << "==" << setw(8) << "Priority" << "==" <<endl<< "-";
    		for( int a = 0 ; a < ppR.GanttChart.size() ; a++ ) {
				fp << ppR.GanttChart.at(a) ; 
			} // for
			fp << endl ; 
		} // if
    	
    	
    	
    	fp<< "===========================================================" << endl << endl ; 
        fp << "Waiting Time" << endl ; 
		fp << std::left << setw(10) << "ID" << std::left << setw(10) <<  "FCFS"<< std::left << setw(10) << "RR" <<
		 std::left << setw(10) << "PSJF" << std::left << setw(10) <<  "NPSJF"<< std::left << setw(10) << "Priority" << endl ;
		fp<< "===========================================================" << endl ;
		for ( int b = 0 ; b < cSet.size() ; b++ ) {
			fp << std::left << setw(10) << cSet.at(b).ID <<std::left << setw(10)<< fcfsR.allData.at(b).WaitingTime <<
		      std::left <<setw(10) << "**" <<std::left << setw(10) << psjfR.allData.at(b).WaitingTime<<std::left << setw(10) <<
			   nsjfR.allData.at(b).WaitingTime <<std::left << setw(10) << ppR.allData.at(b).WaitingTime << endl ;
		} // for
		
		fp<< "===========================================================" << endl << endl ; 
		
		 
        fp << "Turnaround Time" << endl ; 
		fp << std::left << setw(10) << "ID" << std::left << setw(10) <<  "FCFS"<< std::left << setw(10) << "RR" <<
		 std::left << setw(10) << "PSJF" << std::left << setw(10) <<  "NPSJF"<< std::left << setw(10) << "Priority" << endl ;
		fp<< "===========================================================" << endl ;
		for ( int b = 0 ; b < cSet.size() ; b++ ) {
			fp << std::left << setw(10) << cSet.at(b).ID <<std::left << setw(10)<< fcfsR.allData.at(b).TurnaroundTime <<
		      std::left <<setw(10) << "**" <<std::left << setw(10) << psjfR.allData.at(b).TurnaroundTime<<std::left << setw(10) <<
			   nsjfR.allData.at(b).TurnaroundTime <<std::left << setw(10) << ppR.allData.at(b).TurnaroundTime << endl ;
		} // for
		
		fp<< "===========================================================" << endl << endl ;
    }   //end else    
    
    fp.close();//關閉檔案
	
    return true;		// it succeeds if there is at least one records

}   // end writeRecords

//----------------------------------------------------------------------------

void BubbleButt( ressssult & dataa ) {
	for (int i = dataa.allData.size() - 1; i > 0; --i) {   // bubble sort by CPUBurst
        for (int j = 0; j < i; ++j){
        	if (dataa.allData.at(j).Process > dataa.allData.at(j+1).Process) {
        		swap( dataa.allData.at(j), dataa.allData.at(j+1) ) ;
			} // if
                
		} // for
            
   } // for
} // BubbleButt

void CalcuteWaitingTime( ressssult & dataa ) {
	
	for (int i = 0 ; i <  dataa.allData.size() ; i++ ) {   
	//waiting time = turnaround time - cpu burst ;
	
	int sa = 0 ;
        for (int j = 0; j < cSet.size() ; j++){
        	if ( cSet.at(j).ID == dataa.allData.at(i).Process) {
        		sa = j ; 
        		break ;
			} // if
                
		} // for
		
		dataa.allData.at(i).WaitingTime = dataa.allData.at(i).TurnaroundTime - cSet.at(sa).CPUBurst ; 
            
   } // for
} // CalcuteWaitingTime


//----------------------------------------------------------------------------

int main(void)
{ 


ReadAll() ; 
BubbleSort() ; // Sort the Input by Id
nsjfR.GanttChart.clear() ; 
nsjfR.allData.clear() ; 
fcfsR.GanttChart.clear() ; 
fcfsR.allData.clear() ; 
psjfR.GanttChart.clear() ; 
psjfR.allData.clear() ; 
ppR.GanttChart.clear() ; 
ppR.allData.clear() ; 
NSJF() ; 
FCFS() ; 
PSJF() ; 
PP() ;
//for( int a = 0 ; a < cSet.size() ; a++ ) {
//	cout << cSet.at(a).ID << " " << cSet.at(a).CPUBurst << " " << cSet.at(a).ArrivalTime <<
//	" " << cSet.at(a).Priority << endl ; 
//} // for test all token

for( int a = 0 ; a < fcfsR.GanttChart.size() ; a++ ) {
	cout << fcfsR.GanttChart.at(a) ; 
} // for test all token
cout << endl ; 

for( int a = 0 ; a < nsjfR.GanttChart.size() ; a++ ) {
	cout << nsjfR.GanttChart.at(a) ; 
} // for test all token
cout << endl ; 

for( int a = 0 ; a < psjfR.GanttChart.size() ; a++ ) {
	cout << psjfR.GanttChart.at(a) ; 
} // for test all token
cout << endl ; 

for( int a = 0 ; a < ppR.GanttChart.size() ; a++ ) {
	cout << ppR.GanttChart.at(a) ; 
} // for test all token
cout << endl ; 

BubbleButt(ppR) ; 
BubbleButt(psjfR) ; 
BubbleButt(nsjfR) ; 
BubbleButt(fcfsR) ; 
CalcuteWaitingTime(ppR) ;  
CalcuteWaitingTime(psjfR) ; 
CalcuteWaitingTime(nsjfR) ; 
CalcuteWaitingTime(fcfsR) ; 
writeRecords() ; 

nsjfR.GanttChart.clear() ; 
nsjfR.allData.clear() ; 
fcfsR.GanttChart.clear() ; 
fcfsR.allData.clear() ; 
psjfR.GanttChart.clear() ; 
psjfR.allData.clear() ; 
ppR.GanttChart.clear() ; 
ppR.allData.clear() ; 
cSet.clear() ; 
return 0 ;

} // main 
