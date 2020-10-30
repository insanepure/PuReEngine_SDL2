//Engine
#include "PuReCore.h"
class MyScene : public PuRe_Scene
{
public:
    PuRe_Matrix<float>* Matr;
    PuRe_QuadTree* Tree;
    PuRe_Quad* Quad;
    PuRe_Texture* RectText;
    PuRe_Sprite* Sprite;
    PuRe_Material* Mat;
    float32 Cam_X, Cam_Y;
    float32 Time;

    PuRe_Rect MouseRect;
    PuRe_List<PuRe_Rect*> StaticObjects;
    bool collide;

    PuRe_Texture* SpriteTexture;
    PuRe_Texture* FBOTexture;
    PuRe_Material* Mat2;
    PuRe_FrameBuffer* FBO;

    /// METHODS ////
    void Initialize(PuRe_Graphics* graphics)
    {
        PuRe_Vector3(Cam_X, Cam_Y, 1);
        Tree = new PuRe_QuadTree(0, PuRe_Rect(0.0f, 0.0f, graphics->getViewPortWidth(), graphics->getViewPortHeight()));
        Quad = new PuRe_Quad();
        RectText = new PuRe_Texture();
        RectText->LoadDDS("data/textures/stachelfisch.dds");
        Sprite = new PuRe_Sprite(Quad, RectText);
        Cam_X = 0.0f;
        Cam_Y = 0.0f;
        Mat = new PuRe_Material("data/shader/VertexShader.glsl", "data/shader/FragmentShader.glsl");
        glm::mat4 Projection = glm::ortho(0.0f, graphics->getViewPortWidth(), 0.0f, graphics->getViewPortHeight());
        glm::mat4 View = glm::lookAt(glm::vec3(Cam_X, Cam_Y, 1), glm::vec3(Cam_X, Cam_Y, 0), glm::vec3(0, 1, 0));
        glm::mat4 World = glm::mat4(1.0f);
        Mat->setProjection(Projection);
        Mat->setView(View);
        Mat->setModel(World);
        Mat->setResolution(PuRe_Vector2(graphics->getViewPortWidth(), graphics->getViewPortHeight()));

        for (uint16 i = 0; i < 1000; i++)
        {
            int X = std::rand() % (int)graphics->getViewPortWidth();
            int Y = std::rand() % (int)graphics->getViewPortHeight();
            StaticObjects.push_back(new PuRe_Rect((float)X, (float)Y, 16.0f, 16.0f));
        }

        for (uint16 i = 0; i < StaticObjects.size(); i++)
        {
            Tree->Insert(StaticObjects[i]);
        }

        ////Graphics program
        Quad = new PuRe_Quad();
        SpriteTexture = new PuRe_Texture();
        FBOTexture = new PuRe_Texture();
        FBOTexture->Empty(graphics->getViewPortWidth(), graphics->getViewPortHeight());
        FBO = new PuRe_FrameBuffer(FBOTexture);
        SpriteTexture->LoadDDS("data/textures/stachelfisch.dds");
        Sprite = new PuRe_Sprite(Quad, SpriteTexture);

        //Mat2 = new PuRe_Material("data/shader/PassTrough.glsl","data/shader/TestShader.glsl");
        //Mat2->setProjection(glm::ortho( 0.0f, graphics->getViewPortWidth(), graphics->getViewPortHeight(), 0.0f));
        //Mat2->setView(glm::lookAt(glm::vec3(Cam_X,Cam_Y,1),glm::vec3(Cam_X,Cam_Y,0),glm::vec3(0,1,0)));
        //Mat2->setResolution(PuRe_Vector2(graphics->getViewPortWidth(), graphics->getViewPortHeight()));

        //Time = 0.0f;

    }
    bool Update(float timeMultiplicator, PuRe_Graphics* graphics)
    {
        collide = false;
        int16 mX = 0;
        int16 mY = 0;
        SDL_GetMouseState(&mX, &mY);
        MouseRect.Position.X = (float32)mX;
        MouseRect.Position.Y = (float32)mY;
        PuRe_List<PuRe_Rect*> Collide = Tree->GetCollide(&MouseRect);
        printf("Collide Size: %i\n", Collide.size());
        for (uint16 i = 0; i < Collide.size(); i++)
        {
            if (MouseRect.Intersects(Collide[i]))
            {
                collide = true;
                break;
            }
        }
        Time += timeMultiplicator;
        Mat->setTime(Time);
        //Mat2->setTime(Time);
        return true;
    }
    void Render(PuRe_Graphics* graphics)
    {
        //////Bind Shader
        Mat->Bind();
        Tree->Draw(Sprite, Mat);
        PuRe_Vector3 SpritePos(200.0f, 50.0f, 0.0f);
        PuRe_Vector3 Scale(32.0f, 32.0f, 1.0f);
        PuRe_Vector3 Origin(0.0f, 0.0f, 1.0f);
        PuRe_Vector3 Color(1.0f, 0.0f, 0.0f);
        PuRe_Rect Rect(0.0f, 0.0f, 16.0f, 16.0f);
        for (uint16 i = 0; i < StaticObjects.size(); i++)
        {
            SpritePos.X = StaticObjects[i]->Position.X;
            SpritePos.Y = StaticObjects[i]->Position.Y;
            Scale.X = StaticObjects[i]->Width;
            Scale.Y = StaticObjects[i]->Height;
            Sprite->Draw(SpritePos, Scale, Origin, 0.0f, Color, Rect, false, Mat);
        }
        Scale.X = 16.0f;
        Scale.Y = 16.0f;
        if (collide)
        {
            Color.X = 0.0f;
            Color.Y = 1.0f;
        }
        Sprite->Draw(PuRe_Vector3(MouseRect.Position.X, MouseRect.Position.Y, 0.0f), Scale, Origin, 0.0f, Color, Rect, false, Mat);
        SpritePos.X = 0.0f;
        SpritePos.Y = 0.0f;
        Sprite->Draw(SpritePos, Scale, Origin, 0.0f, Color, Rect, false, Mat);
        Mat->UnBind();
        //PuRe_Vector3 SpritePos(200.0f,50.0f,0.0f);
        //PuRe_Vector3 Scale(32.0f,32.0f,1.0f);
        //PuRe_Vector3 Origin(0.0f,0.0f,1.0f);
        //PuRe_Vector3 Color(1.0f,0.0f,0.0f);
        //PuRe_Rect Rect(0.0f,0.0f,16.0f,16.0f);


        //      Mat->Bind();
        //////Draw
        //Sprite->Draw(SpritePos,Scale,Origin,0.0f,Color,Rect,true,Mat);
        //SpritePos.Y += 50.0f;
        ////Sprite->Draw(SpritePos,Scale,Origin,0.0f,Color,Rect,true,Mat);
        ////SpritePos.Y += 50.0f;
        ////Sprite->Draw(SpritePos,Scale,Origin,0.0f,Color,Rect,true,Mat);
        ////SpritePos.Y += 50.0f;
        ////Sprite->Draw(SpritePos,Scale,Origin,0.0f,Color,Rect,true,Mat);
        //Mat->UnBind();

        //
        //Mat2->Bind();
        //Rect.Width = graphics->getViewPortWidth();
        //Rect.Height = graphics->getViewPortHeight();
        //this->FBOTexture->Bind();
        //Mat2->Update();
        //Quad->Draw(Rect,false,graphics->getViewPortWidth(),graphics->getViewPortHeight(),Mat2);
        //this->FBOTexture->UnBind();
        //Mat2->UnBind();
        //Unbind framebuffer


    }
    void Exit()
    {
        delete Tree;
        delete RectText;
        delete Quad;
        delete Sprite;
        delete Mat;

        //delete FBO;
        //delete SpriteTexture;
        //delete FBOTexture;
        //delete Mat2;
    }
};

int PuRe_MAIN
{
    MyScene scene;
    PuRe_EngineDescription description;
    description.Window.Title = "PuReEngine - Development";
    description.Window.Width = 1920 / 2;
    description.Window.Height = 1080 / 2;
    description.Window.X = 100;
    description.Window.Y = 50;
    description.Window.IconPath = "icon.bmp";

    PuRe_Engine* engine = new PuRe_Engine(description);
    engine->Run(&scene);
    delete engine;
    return 0;
}
