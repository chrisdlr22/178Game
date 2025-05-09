#include "_platform.h"

_platform::_platform()
{
    //ctor
    timer->reset();
    scale.x = scale.y = 1.0;

}

_platform::~_platform()
{
    //dtor
}

void _platform::initPlat(const char* file_name, float xCoord, float yCoord, float zCoord, float xScl, float yScl, float zScl, int xFrm, int yFrm, int t, float s, float p_r)
{
    vert[0].x = -1.0; vert[0].y = -1.0; vert[0].z = -1.0;
    vert[1].x =  1.0; vert[1].y = -1.0; vert[1].z = -1.0;
    vert[2].x =  1.0; vert[2].y =  1.0; vert[2].z = -1.0;
    vert[3].x = -1.0; vert[3].y =  1.0; vert[3].z = -1.0;

    pos.x=xCoord;
    pos.y = yCoord;
    pos.z = zCoord;

    switch (t)
    {
case 0:
    type = STATIC;
    break;
case 1:
    type = HORIZONTAL; start_pos = xCoord;
    break;
case 2:
    type = VERTICAL; start_pos = yCoord;
    break;
}

    speed = s;
    patrol_range = p_r;
    moving_forward = true;

    scale.x = xScl;
    scale.y = yScl;
    scale.z = zScl;

    //get frame count
    framesX=xFrm;
    framesY=yFrm;

    xMin=0;
    xMax=1.0/(float)framesX;
    yMax=1.0/(float)framesY;
    yMin=yMax-(1/(float)framesY);

    //tex->loadTexture(file_name);
    tex->loadTexture("images/temp_plat.png");
}

void _platform::drawPlat()
{
    glPushMatrix();
        glTranslatef(pos.x,pos.y,pos.z);
        glScalef(scale.x,scale.y,scale.z);
        glColor3f(1.0,1.0,1.0);

        tex->textureBinder();

        glBegin(GL_QUADS);
        glTexCoord2f(xMin,yMax);
        glVertex3f(vert[0].x,vert[0].y,vert[0].z);

        glTexCoord2f(xMax,yMax);
        glVertex3f(vert[1].x,vert[1].y,vert[1].z);

        glTexCoord2f(xMax,yMin);
        glVertex3f(vert[2].x,vert[2].y,vert[2].z);

        glTexCoord2f(xMin,yMin);
        glVertex3f(vert[3].x,vert[3].y,vert[3].z);
        glEnd();
    glPopMatrix();
}

void _platform::updatePlat()
{
    if(timer->getTicks() > 70)
    {
        switch(type)
    {
        case HORIZONTAL:
        if(moving_forward)
        {
            pos.x += speed;
            if(pos.x > start_pos+patrol_range)
                moving_forward = false;
        }
        else
        {
            pos.x -=speed;
            if(pos.x < start_pos-patrol_range)
                moving_forward = true;
        }
        break;
        case VERTICAL:
            if(moving_forward)
            {
                pos.y += speed;
                if(pos.y > start_pos + patrol_range)
                {
                    moving_forward = false;
                }
            }
            else
            {
                pos.y -=speed;
                if(pos.y<start_pos-patrol_range)
                moving_forward=true;
            }
            break;
        }
        timer->reset();
    }

}

