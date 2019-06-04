#include<cstdlib>
#include<ctime>
#include<stdio.h>
#include<initializer_list>
#include<algorithm>

struct range {
   int start, end;
   range* next;
   range(int start, int end, range* next = nullptr): next(next) {
      this->start = start;
      this->end = end;
   }
   range(std::initializer_list<int> vals): next(nullptr) {
      if (vals.size() != 2) {
         printf("You must provide exactly 2 values in the initializer list!!!");
      }
      auto it = std::begin(vals);
      start = *it;
      ++it;
      end = *it;
   }
   bool collides(range* other) {
      return (start <= other->start and other->start <= end and end <= other->end) or
              (other->start <= start and start <= other->end and other->end <= end) or
              (start <= other->start and other->end <= end) or
              (other->start <= start and end <= other->end);
   }
   bool collides(int start, int end) { 
      return (start <= this->start and this->start <= end and end <= this->end) or
              (this->start <= start and start <= this->end and this->end <= end) or
              (start <= this->start and this->end <= end) or
              (this->start <= start and end <= this->end);
   }
   void collide(range* other) {
      start = std::min(start, other->start);
      end = std::max(end, other->end);
   }
   void collide(int start, int end) {
      this->start = std::min(this->start, start);
      this->end = std::max(this->end, end);
   }
   bool equals(range* other) {
      return start == other->start and end == other->end;
   }
   void print() {
      printf("(%d,%d)\n", start, end);
   }
};

struct ranges {
   range* first;
   ranges(): first(nullptr) {}
   ~ranges() {
      range *next, *curr = first;
      while (curr != nullptr) {
         next = curr->next;
         delete curr;
         curr = next;
      }
   }
   void add_range(int start, int end) {
      if (first == nullptr) {
         first = new range(start, end);
         return;
      }
      if (end < first->start) {
         first = new range(start, end, first);
         return;
      }
      range *next, *curr = first;
      while (curr->next != nullptr and !(curr->collides(start,end)) and end >= curr->next->start)
         curr = curr->next;
      if (curr->collides(start,end))
         curr->collide(start,end);
      else
         curr->next = new range(start, end, curr->next);
      while (curr->next != nullptr and curr->collides(curr->next)) {
         next = curr->next;
         curr->collide(next);
         curr->next = next->next;
         delete next;
      }
   }
   bool equals(ranges* other) {
      range *curr1, *curr2;
      curr1 = first;
      curr2 = other->first;
      while (curr1 != nullptr and curr2 != nullptr) {
         if (!curr1->equals(curr2))
            return false;
         curr1 = curr1->next;
         curr2 = curr2->next;
      }
      if (curr1 == nullptr xor curr2 == nullptr)
         return false;
      return true;
   }
   void print() {
      range* curr = first;
      printf("[");
      while (curr != nullptr) {
         printf("(%d,%d)", curr->start, curr->end);
         if (curr->next != nullptr)
            printf(", ");
         curr = curr->next;
      }
      printf("]\n");
   }
};

#include<iostream>

int count_cover(int N, int R) {
   ranges total;
   ranges target;
   target.add_range(1, N+1);
   int ms = N-R+1;
   int c = 0;
   int i;
   while (!total.equals(&target)) {
      i = (rand() % ms) + 1;
      total.add_range(i, i+R);
      //printf("(%d,%d)\n", i, i+R);
      //total.print();
      //printf("\n");
      //getchar();
      c += 1;
   }
   return c;
}

double count_cover_avg(int N, int R, int T) {
   double total;
   for (int i = 0; i < T; i++) {
      total += count_cover(N, R);
   }
   return total / T;
}

int main(int argc, char* argv[]) {
   if (argc < 3) {
      printf("The correct usage of this program is '%s N R [T]'\n", argv[0]);
      return 1;
   }

   srand(time(0));

   int N = atoi(argv[1]);
   int R = atoi(argv[2]);

   if (argc >= 4) {
      int T = atoi(argv[3]);
      printf("%f\n", count_cover_avg(N,R,T));
   }
   else {
      printf("%d\n", count_cover(N,R));
   }

   return 0;
}
