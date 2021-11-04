#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <stdlib.h>

float dist(float x1, float y1, float x2, float y2)
{
    float x = x1 - x2;
    float y = y1 - y2;
    return sqrt(pow(x, 2) + pow(y, 2));
}

class Body
{
public:
    float x;
    float y;
    float xv;
    float yv;
    float mass;
    std::vector<float> locations;

    void fall(Body other)
    {
        float ox = other.x;
        float oy = other.y;
        float omass = other.mass;

        float angle = atan2(oy - y, ox - x);
        float force = (mass * omass) / pow(dist(ox, oy, x, y), 2);

        float fx = cos(angle) * force;
        float fy = sin(angle) * force;

        xv += fx;
        yv += fy;
    }
    void move()
    {
        x += xv;
        y += yv;
        locations.push_back(x);
        locations.push_back(y);
    }
};

Body body1 = Body();
Body body2 = Body();

int main()
{

    int numBodies = 100;
    std::vector<Body> bodies;
    srand(1);
    for (int i = 0; i < numBodies; i++)
    {
        Body body = Body();
        body.x = rand() % 400 + 200;
        body.y = rand() % 400 + 200;
        body.xv = (rand() % 200) / 100 - 1;
        body.yv = (rand() % 200) / 100 - 1;
        body.mass = rand() % 25 + 12.5;
        bodies.push_back(body);
    }

    int steps = 1000;

    std::ofstream file;
    file.open("../Res/res.txt", std::ostream::out | std::ofstream::trunc);

    for (int i = 0; i < numBodies; i++)
    {
        std::string res = "";
        res += "obj" + std::to_string(i) + "\n";
        res += std::to_string(steps) + "\n";
        res += "255,255,255\n";
        res += "end\n";
        file << res;
    }

    for (int h = 0; h < steps; h++)
    {
        for (int i = 0; i < numBodies; i++)
        {
            for (int j = 0; j < numBodies; j++)
            {
                if (i != j)
                {
                    bodies[i].fall(bodies[j]);
                    bodies[j].fall(bodies[i]);
                    bodies[i].move();
                    bodies[j].move();
                }
            }
        }
        bool mod150 = (h % 150) == 0;
        if (mod150 && h != 0)
        {
            std::cout << mod150 << "\n";
            for (int i = 0; i < numBodies; i++)
            {

                for (int j = 0; j < steps; j += 2)
                {
                    std::string res = "";
                    float x = bodies[i].locations[j];
                    float y = bodies[i].locations[j + 1];
                    res += "obj" + std::to_string(i) + ":" + std::to_string(x) + "," + std::to_string(y) + "\n";
                    file << res;
                }
                bodies[i].locations.clear();
            }
        }
        std::cout << "Step " << h << " Done" << std::endl;
    }
    //write to text file
    for (int i = 0; i < numBodies; i++)
    {
        for (int j = 0; j < steps * 2; j += 2)
        {
            std::string res = "";
            float x = bodies[i].locations[j];
            float y = bodies[i].locations[j + 1];
            res += "obj" + std::to_string(i) + ":" + std::to_string(x) + "," + std::to_string(y) + "\n";
            file << res;
        }
        bodies[i].locations.clear();
    }
    file.close();
    return 0;
}