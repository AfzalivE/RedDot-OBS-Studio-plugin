#ifndef _RTSSINTERFACE_H_INCLUDED_
#define _RTSSINTERFACE_H_INCLUDED_

class RtssInterface
{
public:
		RtssInterface(void);
		void showDot();
		void hideDot();
private:
	bool UpdateOSD(char* lpText);
	void ReleaseOSD();
};

#endif