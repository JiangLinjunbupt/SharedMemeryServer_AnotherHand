#pragma once
#include <vcclr.h>  
#using "../debug/GloveTool.dll"
#using "../debug/GloveLibPC.dll"
using namespace GloveLib;
using namespace GloveTool;

class GloveData
{
public:
	float *HandinfParams;
	GloveData()
	{
		gm = gcnew GloveModel();
		gm->GetSingleton();
		gm->Mychuankou = "COM5";
		gm->Conected();
		gm->SetSocket();
		HandinfParams = new float[26];
	}
	~GloveData() {
		delete HandinfParams;
		gm->CloseSocket = true;
		gm->CloseGloveModel();
	}
	void GetGloveData()
	{
		gm->GetData();
		gm->SkeletonJsonToHandinf(gm->fram);


		//全局平移    //这个从手套得不到，因此设置为零
		HandinfParams[0] = 0;
		HandinfParams[1] = 0;
		HandinfParams[2] = 0;

		//wrist旋转
		HandinfParams[3] = -gm->handinformation->global_pitch_y;
		HandinfParams[4] = -gm->handinformation->global_roll_x + 10;
		HandinfParams[5] = -gm->handinformation->global_yaw_z;


		//thumb
		HandinfParams[6] = -gm->handinformation->fingers[4]->Mcp_z;
		HandinfParams[7] = gm->handinformation->fingers[4]->Mcp_x + 30;

		HandinfParams[8] = 0.5f*gm->handinformation->fingers[4]->Pip;
		HandinfParams[9] = gm->handinformation->fingers[4]->Pip;

		//Index
		HandinfParams[10] = -gm->handinformation->fingers[3]->Mcp_x;
		HandinfParams[11] = -gm->handinformation->fingers[3]->Mcp_z;
		HandinfParams[12] = -gm->handinformation->fingers[3]->Pip;
		HandinfParams[13] = -0.8f*gm->handinformation->fingers[3]->Pip;
		
		//middle
		HandinfParams[14] = -gm->handinformation->fingers[2]->Mcp_x;
		HandinfParams[15] = -gm->handinformation->fingers[2]->Mcp_z;
		HandinfParams[16] = -gm->handinformation->fingers[2]->Pip;
		HandinfParams[17] = -0.8f*gm->handinformation->fingers[2]->Pip;

		//ring
		HandinfParams[18] = -gm->handinformation->fingers[1]->Mcp_x;
		HandinfParams[19] = -gm->handinformation->fingers[1]->Mcp_z;
		HandinfParams[20] = -gm->handinformation->fingers[1]->Pip;
		HandinfParams[21] = -0.8f*gm->handinformation->fingers[1]->Pip;

		//pinkey
		HandinfParams[22] = -gm->handinformation->fingers[0]->Mcp_x;
		HandinfParams[23] = -gm->handinformation->fingers[0]->Mcp_z;
		HandinfParams[24] = -gm->handinformation->fingers[0]->Pip;
		HandinfParams[25] = -0.8f*gm->handinformation->fingers[0]->Pip;


		//规范一下，让手模看起来更合理
		HandinfParams[11] = HandinfParams[11] + 5;
		if (HandinfParams[19] < 14 && HandinfParams[19] > -10.0)
		{
			HandinfParams[19] = (HandinfParams[19] - 8.0f) < -10.0f ? -10.0f : (HandinfParams[19] - 8.0f);
		}
		if (HandinfParams[23] < 19)
		{
			HandinfParams[23] = (HandinfParams[23] - 15.0f) < -10.0f ? -10.0f : (HandinfParams[23] - 15.0f);
		}
		HandinfParams[15] = 0;

		//for (int i = 0; i < 24; i++)
		//{
		//	if (i == 15 || i == 16 || i == 17)
		//	{
		//		if (HandinfParams[i] < 0)
		//		{
		//			HandinfParams[i] = HandinfParams[i] + 360.0;
		//		}
		//	}
		//	else
		//	{
		//		if (HandinfParams[i] > 200)
		//		{
		//			HandinfParams[i] = HandinfParams[i] - 360;
		//		}
		//		else if (HandinfParams[i]<-180)
		//		{
		//			HandinfParams[i] = HandinfParams[i] + 360;
		//		}
		//		else
		//		{
		//			;
		//		}
		//	}
		//}
	}

private:
	gcroot<GloveModel^> gm;
};
