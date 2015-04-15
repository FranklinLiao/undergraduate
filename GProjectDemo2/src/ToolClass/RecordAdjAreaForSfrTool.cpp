#include "stdafx.h"
#include "RecordAdjAreaForSfrTool.h"
//************************************  
// 函数名称: recordAdjAreaForSfrTool     
// 函数说明： 判断小区是否相邻    
// 作者:Franklin     
// 日期：2015/04/13     
// 返 回 值: void     
//************************************
void RecordAdjAreaForSfrTool::recordAdjAreaForSfrTool() {
	/*
	int areaCnt = DBHelper::queryTableInfoNum("Area");
	int gridCnt = DBHelper::queryTableInfoNum("Grid");
	for(int i =0;i<=areaCnt;i++) {

	}
	*/
	string info = "declare @mAid int\
		declare @oAid int\
		declare @gridIndex int\
		declare @matchcnt int\
		declare @serverCnt int\
		declare @adjCnt int\
		declare @serverRsrp float\
		declare @adjRsrp float\
		declare @serverAreaCursor cursor\
		declare @otherAreaCursor cursor\
		declare @gridCursor cursor\
		set @serverAreaCursor = cursor for\
		select Aid  from Area  order by AId;\
	Open @serverAreaCursor\
		fetch next from @serverAreaCursor into @mAid\
		while @@FETCH_STATUS = 0\
			begin\
			set @matchcnt = 0;\
	set @otherAreaCursor = cursor for\
		select Aid from Area where Aid != @mAid order by AId;\
	open @otherAreaCursor\
		fetch next from @otherAreaCursor into @oAid\
		while @@FETCH_STATUS =0\
			begin\
			set @gridCursor = cursor for\
			select GId  from Grid where GAId = @mAid order by GId;\
			Open @gridCursor\
		fetch next from @gridCursor into @gridIndex\
		while @@FETCH_STATUS = 0\
			begin\
			select @serverRsrp = GRSRP  from GridFieldStrenth where AId = @oAid and GId = @gridIndex\
			select @adjRsrp = GRSRP from GridFieldStrenth where AId = @mAid and GId = @gridIndex\
			if(@serverRsrp - @adjRsrp > 6)\
				begin\
				set @matchcnt = @matchcnt+1\
				end\
				fetch next from @gridCursor into @gridIndex\
				end\
				close @gridCursor\
				deallocate @gridCursor\
				fetch next from @otherAreaCursor into @oAid\
				end\
				close @otherAreaCursor\
				deallocate @otherAreaCursor\
				select @serverCnt = count(*) from Grid where GAId = @mAid\
				select @adjCnt = count(*)  from Grid where GAId = @oAid\
				if(@serverCnt + @adjCnt!=0)\
					if(@matchcnt/(@serverCnt+@adjCnt) > 0.3)\
						begin\
						insert into ANeighbourCell (Aid,ANeighbourCellId) values(@mAid,@oAid);\
	end\
		fetch next from @serverAreaCursor into @mAid\
		end\
		close @serverAreaCursor\
		deallocate @serverAreaCursor";
	DBHelper::insertStringInfo(info);
}