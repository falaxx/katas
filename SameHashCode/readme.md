# Hash Code

Could you please complete and return the answer to this programming question

It should compile and work. You can use the internet as you would normally in your daily work life but all the code you submit should be your own.

Please only send 1 .cs file with all your code.


Write a method that will produce three (3) different strings (different string values) that have the same hash code such that:
```
stringA.GetHashCode() == stringB.GetHashCode() && !String.Equals(stringA, stringB) &&

stringB.GetHashCode() == stringC.GetHashCode() && !String.Equals(stringB, stringC) &&

!String.Equals(stringA, stringC)
```

# Solution 

For my solution first I did this in C# since the std::hash (corresponding to GetHashCode() in C#) returns lot more digits in C++, so collisions are more rare, and my solution would not be relevant in term of time execution versus other C# solution. It made me learn a bit of C# as well , created my first .net project wich was interesting.

For me the problem was creating and incrementing strings fast to check their HashCodes.

I choosed to use ints wich I incremented, and check their hashcodes with ToString(), for faster computing instead of creating a function to create and increment strings.

I tried differents containers to save hashcodes, but a dictionnary of int/int was the fastest, also tried to multitread whenever I encountered duplicate hashcodes to find the 3rd occurence, but it was not faster.

Since dictionnary doesn't allow more than one item of the same key and throw an exeption otherwise, I create two dictionnary for first and second occurence, and when the 2d throw an exeption, I can return the three strings directly by using the 3rd hashcode in the 1st and 2d dictionnary.

I put timer and tester in the main to check performances and reliability, so I launch the function 20 times to see best,worst and average computing time, wich depends of luck factor, that's why my starting strings change everytime the function is called with use of Random().

Compile with dotnet build / dotnet run.
