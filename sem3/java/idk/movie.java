import java.util.*;
class Movie implements Comparable<Movie>
{
    String name;
    int rating;
    int year;
    Movie(String s,int r, int y)
    {
        name=s;
        year=y;
        rating=r;
    }
    public String toString()
    {
        return name+"   "+rating+"  "+year;
    }
    public int compareTo(Movie s2) { 
       // System.out.println(rating+ "888888"+s2.rating);
               if (rating > s2.rating) 
                   return 1; 
                else if (rating < s2.rating) 
                    return -1; 
               else if(rating==s2.rating)
               {
                if(year>s2.year)
                    return 1;
                else if(year<s2.year)
                    return -1;
                else
                   return 0; 
               }
               else
                  return 0;
                   //int val=rating-s2.rating;
                   
                   
                } 
}


class MyYearComparator implements Comparator<Movie>{ 
              
            // Overriding compare()method of Comparator  
                        // for descending order of cgpa 
            public int compare(Movie s1, Movie s2) { 
                if(s1.year>s2.year)
                    return 1;
                else if(s1.year<s2.year)
                    return -1;
                else
                   return 0; 
                } 
        } 
class MyRatingComparator implements Comparator<Movie>{ 
              
            // Overriding compare()method of Comparator  
                        // for descending order of cgpa 
            public int compare(Movie s1, Movie s2) { 
                if (s1.rating > s2.rating) 
                   return 1; 
                else if (s1.rating < s2.rating) 
                    return -1; 
               else
                   return 0; 
                } 
        }         
        
class MyClass {
    public static void main(String args[]) {
     // Queue<Movie> q=new PriorityQueue<Movie>();//new MyComparator()); // priority queue with 2 cond
     // Queue<Movie> q=new LinkedList<Movie>();//new MyComparator());  simple LL
      List<Movie> q=new LinkedList<Movie>();
      //Queue<Movie> q=new ArrayDeque<Movie>();
      
      System.out.println(q);
      q.add(new Movie("LionKing",4,2018));
      System.out.println(q);
      q.add(new Movie("NVP",5,2002));
      System.out.println(q);
      q.add(new Movie("Chandrayan",2,2019));
      System.out.println(q);
      q.add(new Movie("Mars",4,2020));
      for(Movie m:q)
      {System.out.println(m);}
      //System.out.println(q.peek());
      System.out.println(q);
      Collections.sort(q);
      System.out.println(q);
      Collections.sort(q, new MyYearComparator());
      System.out.println(q);
      Collections.sort(q, new MyRatingComparator());
      System.out.println(q);
    }
}



