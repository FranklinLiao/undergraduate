
// GProjectDemo2Doc.h : CGProjectDemo2Doc ��Ľӿ�
//


#pragma once


class CGProjectDemo2Doc : public CDocument
{
protected: // �������л�����
	CGProjectDemo2Doc();
	DECLARE_DYNCREATE(CGProjectDemo2Doc)

// ����
public:

// ����
public:

// ��д
public:
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CGProjectDemo2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
