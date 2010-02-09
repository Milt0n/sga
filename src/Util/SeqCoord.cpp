//-----------------------------------------------
// Copyright 2009 Wellcome Trust Sanger Institute
// Written by Jared Simpson (js18@sanger.ac.uk)
// Released under the GPL
//-----------------------------------------------
//
// SeqCoord - A data structure holding the coordinate
// of a substring of a sequence which consists of an interval and
// the length of the string. Used to build matches and overlaps.
//
#include "SeqCoord.h"

// Return a seqcoord representing the complement of the interval
// For example if the seqcoord represents the matched portion of a string, 
// this returns a seqcoord of the unmatched portion
SeqCoord SeqCoord::complement() const
{
	assert(isExtreme());

	SeqCoord out;
	out.seqlen = seqlen;

	if(isLeftExtreme())
	{
		out.interval.start = std::max(interval.start, interval.end) + 1;
		out.interval.end = out.seqlen - 1;
	}
	else
	{
		out.interval.start = 0;
		out.interval.end = std::min(interval.start, interval.end) - 1;
	}
	assert(out.interval.start <= out.interval.end);
	return out;
}

// Returns the substring of STR described by this seqcoord
std::string SeqCoord::getSubstring(const std::string& str) const
{
	int left;
	int size; 
	if(interval.start < interval.end)
	{
		left = interval.start;
		size = interval.end - interval.start + 1;
	}
	else
	{
		left = interval.end;
		size = interval.start - interval.end + 1;
	}
	return str.substr(left, size);
}

// Returns the substring of STR that is NOT contained in the interval
// described by this seqcoord
std::string SeqCoord::getComplementString(const std::string& str) const
{
	SeqCoord comp = complement();
	return comp.getSubstring(str);
}


// Output
std::ostream& operator<<(std::ostream& out, const SeqCoord& sc)
{
	out << sc.interval << " " << sc.seqlen;
	return out;
}

// Input
std::istream& operator>>(std::istream& in, SeqCoord& sc)
{
	in >> sc.interval >> sc.seqlen;
	return in;
}

