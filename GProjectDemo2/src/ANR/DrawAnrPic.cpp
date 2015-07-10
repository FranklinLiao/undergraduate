#include "stdafx.h"
#include "DrawAnrPic.h"
void DrawAnrPic::drawPic(vector<double> nrtPercent,vector<double> nrtCnt) {
	double nrtPercentArray[2];
	double nrtCntArray[2];
	vector<double>::iterator iter = nrtPercent.begin();
	int i=0;
	while(iter!=nrtPercent.end()) {
		nrtPercentArray[i] = *iter++;
		i++;
	}
	iter = nrtCnt.begin();
	i=0;
	while(iter!=nrtCnt.end()) {
		nrtCntArray[i] = *iter++;
		i++;
	}

	Engine* m_pEngine;
	mxArray *_nrtPercent = NULL;
	mxArray *_nrtCnt = NULL;
	m_pEngine = engOpen(NULL);
	if( m_pEngine == NULL ) {
		cout<<"error!"<<endl;
		exit(-1);
	}

	//double y1[9] = {0,   2.827/9   , 10.2687/9   , 15.465/9  ,  19.3475/9 ,  23.769/9 ,  26.688/9  ,   32.155/9 ,    36.284/9};
	//double y2[9] = {0,   3.292/9   , 8.2671/9   ,16.416/9   , 22.601/9   , 25.7154/9  , 29.183/9  ,  34.855/9 ,   40.9438/9};

	
	_nrtPercent = mxCreateDoubleMatrix(1, 2, mxREAL);
	_nrtCnt = mxCreateDoubleMatrix(1, 2, mxREAL);
	memcpy((void *)mxGetPr(_nrtPercent), (void *)nrtPercentArray, sizeof(nrtPercentArray));
	memcpy((void *)mxGetPr(_nrtCnt), (void *)nrtCntArray, sizeof(nrtCntArray));
	
	engPutVariable(m_pEngine, "yPercent", _nrtPercent);
	engPutVariable(m_pEngine, "yCnt", _nrtCnt);
	
	//engEvalString(m_pEngine,"y1 = [0   2.827/9    10.2687/9    15.465/9    19.3475/9   23.769/9   26.688/9     32.155/9     36.284/9]");
	//engEvalString(m_pEngine,"y2 = [0   3.292/9    8.2671/9   16.416/9    22.601/9    25.7154/9   29.183/9    34.855/9    40.9438/9]");
	engEvalString(m_pEngine, "xPercent={'邻区优化前','邻区优化后'}");
	engEvalString(m_pEngine, "subplot(2,1,1);");
	engEvalString(m_pEngine, "bar(yPercent,0.2,'b');");
	engEvalString(m_pEngine, "a=get(gca);");
	engEvalString(m_pEngine, "ax=a.XLim;%获取横坐标上下限");
	engEvalString(m_pEngine, "ay=a.YLim;%获取纵坐标上下限");
	engEvalString(m_pEngine, "k=[0.13 0.83];%给定text相对位置");
	/*
	engEvalString(m_pEngine, "for i=1:2");
	engEvalString(m_pEngine, "x0=ax(1)+k(i)*(ax(2)-ax(1));%获取text横坐标");
	engEvalString(m_pEngine, "y0=yPercent(i)-3;%获取text纵坐标");
	engEvalString(m_pEngine, "text(x0,y0,num2str(yPercent(i)),'Color','r')");
	engEvalString(m_pEngine, "end");
	*/
	engEvalString(m_pEngine, "text(ax(1)+k(1)*(ax(2)-ax(1)),yPercent(1)-3,num2str(yPercent(1)),'Color','r')");
	engEvalString(m_pEngine, "text(ax(1)+k(2)*(ax(2)-ax(1)),yPercent(2)-3,num2str(yPercent(2)),'Color','r')");
	engEvalString(m_pEngine, "set(gca,'ytick',0:10:100)");
	engEvalString(m_pEngine, "set(gca, 'XTickLabel', xPercent)");
	engEvalString(m_pEngine, "ylabel('小区切换成功率(%)')");

	engEvalString(m_pEngine, "xCnt={'邻区优化前','邻区优化后'}");
	engEvalString(m_pEngine, "subplot(2,1,2);");
	engEvalString(m_pEngine, "bar(yCnt,0.2,'b'); ");
	engEvalString(m_pEngine, "set(gca,'ytick',0:5:30)");
	engEvalString(m_pEngine, "set(gca, 'XTickLabel', xCnt)");
	engEvalString(m_pEngine, "ylabel('小区平均邻区数(个)')");

	MessageBox(NULL,_T("已经得到邻区优化前和优化后的仿真结果"),_T("通知"),MB_OK);
	engClose(m_pEngine);
}