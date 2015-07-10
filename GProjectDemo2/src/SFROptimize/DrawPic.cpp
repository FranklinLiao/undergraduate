#include "stdafx.h"
#include "DrawPic.h"
void DrawPic::drawPic(vector<double> edgeOldSfr,vector<double> edgeNewSfr,vector<double> allOldSfr,vector<double> allNewSfr) {
	double edgeOldSfrArray[9];
	double edgeNewSfrArray[9];
	double allOldSfrArray[9];
	double allNewSfrArray[9];
	vector<double>::iterator iter = edgeOldSfr.begin();
	int i=0;
	while(iter!=edgeOldSfr.end()) {
		edgeOldSfrArray[i] = *iter++;
		i++;
	}
	iter = edgeNewSfr.begin();
	i=0;
	while(iter!=edgeNewSfr.end()) {
		edgeNewSfrArray[i] = *iter++;
		i++;
	}
	iter = allOldSfr.begin();
	i=0;
	while(iter!=allOldSfr.end()) {
		allOldSfrArray[i] = *iter++;
		i++;
	}
	iter = allNewSfr.begin();
	i=0;
	while(iter!=allNewSfr.end()) {
		allNewSfrArray[i] = *iter++;
		i++;
	}
	Engine* m_pEngine;
	mxArray *_edgey1 = NULL;
	mxArray *_edgey2 = NULL;
	mxArray *_ally1 = NULL;
	mxArray *_ally2 = NULL;
	m_pEngine = engOpen(NULL);
	if( m_pEngine == NULL ) {
		cout<<"error!"<<endl;
		exit(-1);
	}

	//double y1[9] = {0,   2.827/9   , 10.2687/9   , 15.465/9  ,  19.3475/9 ,  23.769/9 ,  26.688/9  ,   32.155/9 ,    36.284/9};
	//double y2[9] = {0,   3.292/9   , 8.2671/9   ,16.416/9   , 22.601/9   , 25.7154/9  , 29.183/9  ,  34.855/9 ,   40.9438/9};

	engEvalString(m_pEngine, "x = 0:10:80;");
	_edgey1 = mxCreateDoubleMatrix(1, 9, mxREAL);
	_edgey2 = mxCreateDoubleMatrix(1, 9, mxREAL);
	_ally1 = mxCreateDoubleMatrix(1, 9, mxREAL);
	_ally2 = mxCreateDoubleMatrix(1, 9, mxREAL);
	memcpy((void *)mxGetPr(_edgey1), (void *)edgeOldSfrArray, sizeof(edgeOldSfrArray));
	memcpy((void *)mxGetPr(_edgey2), (void *)edgeNewSfrArray, sizeof(edgeNewSfrArray));
	memcpy((void *)mxGetPr(_ally1), (void *)allOldSfrArray, sizeof(allOldSfrArray));
	memcpy((void *)mxGetPr(_ally2), (void *)allNewSfrArray, sizeof(allNewSfrArray));
	engPutVariable(m_pEngine, "edgeOldSfr", _edgey1);
	engPutVariable(m_pEngine, "edgeNewSfr", _edgey2);
	engPutVariable(m_pEngine, "allOldSfr", _ally1);
	engPutVariable(m_pEngine, "allNewSfr", _ally2);
	//engEvalString(m_pEngine,"y1 = [0   2.827/9    10.2687/9    15.465/9    19.3475/9   23.769/9   26.688/9     32.155/9     36.284/9]");
	//engEvalString(m_pEngine,"y2 = [0   3.292/9    8.2671/9   16.416/9    22.601/9    25.7154/9   29.183/9    34.855/9    40.9438/9]");
	engEvalString(m_pEngine,"subplot(2,1,1);");
	engEvalString(m_pEngine, "plot(x,edgeOldSfr,x,edgeNewSfr,'o-.');");
	engEvalString(m_pEngine, "xlabel('小区用户数(个)','FontSize',12);");
	engEvalString(m_pEngine, "ylabel('小区边缘用户吞吐量(Mb/s)','FontSize',12);");
	engEvalString(m_pEngine, "legend('固定SFR','D-SFR','FontSize',12,2);");

	engEvalString(m_pEngine,"subplot(2,1,2);");
	engEvalString(m_pEngine,"plot(x,allOldSfr,x,allNewSfr,'o-.');");
	engEvalString(m_pEngine,"xlabel('小区用户数(个)','FontSize',12);");
	engEvalString(m_pEngine, "ylabel('小区吞吐量(Mb/s)','FontSize',12);");
	engEvalString(m_pEngine, "legend('固定SFR','D-SFR','FontSize',12,2);");

	MessageBox(NULL,_T("已经得到固定软频率复用和动态软频率复用仿真结果"),_T("通知"),MB_OK);
	engClose(m_pEngine);
}