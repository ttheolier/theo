#ifndef QSORT_H
#define QSORT_H

#include <vector>
#include <algorithm>

//STABILITY
template<class T, class TComparator>
T& median_of_three(T& a, T& b, T& c, TComparator comparator) {
    // TODO: implement.
    //if distinct values
    if (comparator(b,a) ^ comparator(b,c))
    {
    	return b;
    }
    else if(comparator(a,b)^comparator(a,c))
    {
    	return a;
    }
    else if (comparator(c,a)^comparator(c,b)) 
    {
    	return c;
    }
    //In case of tie
    else 
    {
    	//if theres a two way tie with a return a
    	if ((comparator(a,b)&&comparator(b,a))||(!comparator(a,b)&&!comparator(b,a)))
    	{
    		return a;
    	}
    	//if two way tie with a return a
    	else if((comparator(a,c)&&comparator(c,a))||(!comparator(a,c)&&!comparator(c,a)))
    	{
    		return a;
    	}
    	//either two way tie with c, or three way tie, either way return c
    	else
    	{
    		return c;
    	}
    }
	    	
}
//ORDER OF FUNCTIONS MIGHT MATTER
template<class T>
int doswaps(std::vector<T>& vec,size_t one,size_t two)
{
	//simple swap
	T temp = vec[one];
	vec[one] = vec[two];
	vec[two] = temp;
	return one;
	
}

template<class T, class TComparator>
size_t partition(std::vector<T>& vec, TComparator& comparator, size_t low, size_t high) {
	  // TODO: implement.
	//sets i indexing variable
	int i = low-1;
	//get pivot
	T piv;
	//block of code ensures that median of three will not compare identical objects
	if (high-low >=2)
	{
		piv = median_of_three(vec[low],vec[(high-low)/2 + low],vec[high],comparator);
	}
	//if there are 2 objects it arbitrarily picks the last element because median of three wont work here
	else
	{
		piv = vec[high];
	}

	//print for debugging
	/*for (unsigned int k = low; k < high+1; k++) {
        std::cerr << vec[k] << " ";
    }
    std::cerr << std::endl;*/

    //check from end to beggining to swap pivot to end, this order ensures stable sort
	if ((comparator(piv,vec[high]) && comparator(vec[high],piv))||(!comparator(piv,vec[high]) && !comparator(vec[high],piv))) 
	{
		//does nothing, nothing to swap
	}
	//swaps middle to the end
	else if ((comparator(piv,vec[(high-low)/2+low]) && comparator(vec[(high-low)/2+low],piv))
		||(!comparator(piv,vec[(high-low)/2+low]) && !comparator(vec[(high-low)/2+low],piv)))
	{
		doswaps(vec,(high-low)/2+low,high);
	}
	//swaps beggining value to end
	else
	{
		doswaps(vec,low,high);
	}

	//print for debugging
	/*for (unsigned int k = low; k < high+1; k++) {
        std::cerr << vec[k] << " ";
    }
    std::cerr << std::endl;*/

    //move pivot to correct place (sort)
	for (unsigned int j = low;j<high;j++)
	{
		if (!comparator(piv,vec[j]))
		{
			i++;
			doswaps(vec,i,j);
		}
	}
	doswaps(vec,i+1,high);

	//print for debugging
	/*
	for (unsigned int k = low; k < high+1; k++) {
        std::cerr << vec[k] << " ";
    }
    std::cerr << std::endl;*/

    //return pivot position
	return i+1;
}

template<class T, class TComparator>
void QuickSortHelper(std::vector<T>& vec, int low, int high, TComparator& comparator)
{
	//Base Case, if everything is sorted
	if (low>=high)
	{
		return;
	}
	//Else case
	else
	{
		//partition and get pivot
		unsigned int piv = partition(vec,comparator,low,high);
		//std::cerr<<piv<<std::endl;
		//lower half
		QuickSortHelper(vec,low,piv-1,comparator);
		//upper half
		QuickSortHelper(vec,piv+1,high,comparator);
	}

}

template<class T, class TComparator>
void quicksort(std::vector<T>& vec, TComparator comparator) {
    // TODO: implement.
    //Acts as wrapper, calling helper function
    return QuickSortHelper(vec,0,vec.size()-1, comparator);
}









#endif
