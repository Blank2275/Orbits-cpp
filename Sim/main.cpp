#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

double dist(double x1, double y1, double x2, double y2)
{
    double x = x1 - x2;
    double y = y1 - y2;
    return sqrt(pow(x, 2) + pow(y, 2));
}

class Body
{
public:
    double x;
    double y;
    double xv;
    double yv;
    double mass;
    std::vector<std::vector<double> > locations;

    void fall(Body other)
    {
        double ox = other.x;
        double oy = other.y;
        double omass = other.mass;

        double angle = atan2(ox - x, oy - y);
        double force = (mass * omass) / pow(dist(ox, oy, x, y), 2);

        double fx = cos(angle) * force;
        double fy = sin(angle) * force;

        xv += fx;
        yv += fy;
    }
    void move()
    {
        x += xv;
        y += yv;
        std::vector<double> pos;
        pos.push_back(x);
        pos.push_back(y);
        locations.push_back(pos);
    }
};

Body body1 = Body();
Body body2 = Body();

int main()
{
    int numBodies = 10;
    std::vector<Body> bodies;
    for(int i = 0; i < numBodies; i++){
        Body body = Body();
        body.x = i * 100;
        body.y = 400;
        body.xv = 0;
        body.yv = 0;
        body.mass = 100;
        bodies.push_back(body);
    }

    int steps = 50;
    for(int h = 0; h < steps; h++){
        for(int i = 0; i < numBodies; i++){
            for(int j = 0; j < numBodies; j++){
                if(i != j){
                    bodies[i].fall(bodies[j]);
                    bodies[j].fall(bodies[i]);
                    bodies[i].move();
                    bodies[j].move();
                }
            }
        }
    }
    //write to text file
    std::ofstream file;
    file.open("../Res/res.txt");
    for(int i = 0; i < numBodies; i++){
        std::string res = "";
        res += "obj"+std::to_string(i)+"\n";
        res += std::to_string(steps)+"\n";
        res += "255,255,255\n";
        for(int j = 0; j < steps; j++){
            std::vector<double> location = bodies[i].locations[j];
            res += std::to_string(location[0]) + "," + std::to_string(location[1]) + "\n";
        }
        res += "end\n";
        file<<res;
    }
    file.close();
    return 0;
}