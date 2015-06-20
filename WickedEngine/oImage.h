#pragma once
#include "Image.h"

class oImage : public Image
{
private:
	string texture, mask, normal;
	ID3D11ShaderResourceView* texturePointer,*normalPointer,*maskPointer;
public:
	oImage();
	oImage(const string& newTexture, const string& newMask, const string& newNormal);
	oImage(const string& newTexture, const string& newMask);
	oImage(const string& newTexture);
	void Init();
	void CreateReference(const string& newTexture, const string& newMask, const string& newNormal);
	void CleanUp();

	void Update(float);
	void Update();
	void Draw(ID3D11ShaderResourceView* refracRes, ID3D11DeviceContext* context);
	void Draw();
	void DrawNormal(ID3D11DeviceContext* context);

	string name;

	ImageEffects effects;

	struct Anim{
		struct MovingTexData{
			float speedX,speedY;
			MovingTexData(){
				speedX=speedY=0;
			}
		};
		struct DrawRecData{
			float onFrameChangeWait,elapsedFrames,currentFrame,frameCount;
			float jumpX,jumpY;
			float sizX,sizY;

			DrawRecData(){
				onFrameChangeWait=elapsedFrames=currentFrame=frameCount=0;
				jumpX=jumpY=0;
				sizX=sizY=0;
			}
		};

		bool repeatable;
		XMFLOAT3 vel;
		float rot,scaleX,scaleY,opa,fad;
		MovingTexData movingTexAnim;
		DrawRecData drawRecAnim;

		Anim(){
			repeatable=false;
			vel=XMFLOAT3(0,0,0);
			rot=scaleX=scaleY=opa=fad=0;
			movingTexAnim=MovingTexData();
			drawRecAnim=DrawRecData();
		}
	};
	Anim anim;
	
	ID3D11ShaderResourceView* getTexture(){return texturePointer;}
	void setTexture(ID3D11ShaderResourceView* value){texturePointer=value;}
};
