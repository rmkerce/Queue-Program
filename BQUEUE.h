class bqnode
{
    public:
        int time;
        bqnode *prev, *next;
};

class BQUEUE
{
    public:
        BQUEUE();
        ~BQUEUE();
       BQUEUE(const BQUEUE & ORG);
       void Enqueue(int);
       void Dequeue( );
       void Print( );
   private:
       bqnode *front;//use ONLY one pointer
};
