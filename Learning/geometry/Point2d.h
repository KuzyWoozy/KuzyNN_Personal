#ifndef guard
#define guard
class Point2d {   
    private:
        int m_x;
        int m_y;

    public:
        Point2d(int x=0, int y=0);
        void Print();
        void Dist(Point2d& point);
};
#endif
