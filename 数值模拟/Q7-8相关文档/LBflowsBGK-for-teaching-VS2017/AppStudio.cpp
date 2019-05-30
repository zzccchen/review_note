//========================================================//
//              MRT LBM code                              //
//========================================================//
// Author      : SUN DongKe                               //
// Copyright   : All rights reserved.                     //
// Description : C++, Ansi-style                          //
// Last updated: 2012.10.07 by SUN DongKe                 //
//========================================================//
// SUN DongKe, Ph.D                                       //
// Website     : http://www.calcflows.com                 //
// E-Mail      : sundongke@gmail.com                      //
//========================================================//

#include "LBMStudio.h"

//Ö÷³ÌÐò
void main()
{	
	int iter=0;//.....iteration counter		
	int iterMax=0;//.....maximum number of iterations
	int frame=0;
	int frameMax=0;	

	Information();

	ReadPara(error, iterMax, frameMax);

	CLBFlowBGK *Flow=new CLBFlowBGK();

	Flow->Initialize();

	Flow->WriteFlow(frame++);	

	//..main loop
	for(iter = 0; iter<=iterMax; iter++)
	{		
		if(iter>=1&&iter%(iterMax/frameMax)==0)
		{
			cout << "Frame: "<<frame << endl;
			Flow->CheckFlow(iter);					
			Flow->WriteFlow(frame);

			frame++;
		}
		Flow->Propagate();		

		Flow->Relaxation(); 

		Flow->Bounceback(); 

		Flow->Boundary(); 
	}
	//end of the main loop

	delete Flow;
	cout<<"*****************    end     ********************\n";	 
}

