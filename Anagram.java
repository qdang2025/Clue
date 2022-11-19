package com.gradescope.anagram; // DO NOT MODIFY PACKAGE NAME OR CLASS NAME

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Anagram {

	// The type of the dictionary variable can be of your choice.
	private ArrayList<String> dictionary;
	private Word[] words;

	// Load dictionary.txt on class load
	public Anagram(String dictionaryFilename) {
		this.dictionary = loadDictionary(dictionaryFilename);
		this.words = copyDictionary(dictionary);
	}

	// Read the dictionary file into some data structure of your choice. ArrayList
	// is given as an example.
	public ArrayList<String> loadDictionary(String filename) {
		// You can use any other data structure as well, provided you build it from
		// scratch
		// or use some primitive data structure like list.
		ArrayList<String> dictionary = new ArrayList<String>();
		try {
			// Read the file here.
			Scanner sc = new Scanner(new File(filename));
			while (sc.hasNextLine()) {
				dictionary.add(sc.nextLine());
			}
			sc.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		return dictionary;
	}


	/**
	 * Implement the algorithm here. Do not change the function signature.
	 * The return type should be ArrayList<ArrayList<String>>, so that Gradescope
	 * can read your output.
	 * Your output need not be sorted.
	 * 
	 * @returns - List of anagram classes, where each element in the list is a list
	 *          of all the words in that anagram class.
	 */
	public ArrayList<ArrayList<String>> getAnagrams() {
		ArrayList<ArrayList<String>> anagrams = new ArrayList<ArrayList<String>>();
		// Step 1: Iterate through the word array and sort each word in the ASCII
		// lexicographical order
		int max = 0;
		for (int i = 0; i < words.length; i++) { // O(nk)
			words[i].word = countingSort(words[i].word); // O(k)
			if (words[i].word.length() > max) {
				max = words[i].word.length();
			}
		}
		// Step 2: Sort the array of words
		words = radixSort(words, max); // - O(n*maxk) 
		// Step 3: Iterate through the sorted array and add each word to the anagram list
		anagrams = group(words); // - O(n)
		return anagrams;
	}

	/**
	 * You can use this method for testing and debugging if you wish.
	 */

	public static void main(String[] args) {
		Anagram pf = new Anagram("dictionary.txt");
		System.out.print(pf.getAnagrams());
	}

	// A class Word that stores the string and its correspoding index in the
	//original dictionary
	public class Word {
		private String word;
		private int index;

		public Word(String word, int index) {
			this.word = word;
			this.index = index;
		}
	}

	// A method that copies the dictionary into an array of Word objects
	// Type signature: ArrayList<String> -> Word[]
	public Word[] copyDictionary(ArrayList<String> d) {
		Word[] words = new Word[d.size()];
		for (int i = 0; i < d.size(); i++) {
			words[i] = new Word(d.get(i), i);
		}
		return words;
	}

	// A method that sorts a string in ascii order using counting sort
	// The strings has characters from ascii 97 to 122 (26 characters)
	// Type signature: String -> String
	public String countingSort(String s) {
		int[] count = new int[26];
		for (int i = 0; i < s.length(); i++) { // Runs in O(k)
			count[s.charAt(i) - 'a']++;
		}
		String sorted = "";
		for (int i = 0; i < count.length; i++) { // Runs in O(26) = O(1)
			for (int j = 0; j < count[i]; j++) { // Runs in O(k)
				sorted += (char) (i + 'a');
			}
		}
		return sorted;
	}

	// A method that sorts a Word array using radix sort based on the ASCII values of the strings
	// Sort the strings in base 26 from their most significant digit to their least significant digit
	// The method uses counting sort to sort the strings stably.
	// Type signature: Word[] -> Word[]
	public Word[] radixSort(Word[] words, int d) {
		for (int i = d - 1; i >= 0; i--) { // Runs in O(k)
			words = countingSort(words, i, d);
		}
		return words;
	}

	// A method that sorts a Word array using counting sort based on the ASCII values of the strings
	// Sort the strings in base 26 at their input digit, if the input digit is
	// greater than the length of the string, consider that digit to have the lowest ascii value, even lower than the lowest letter in range
	//Make a counter array of size 27 to account for the string length being less than the max length
	//For any strings that have values at the digit index, the corresponding index value will be incremented by 1
	//When transferring the values from the counter array to the sorted array, the index of the counter array is decremented by 1 to 
	//account for the fact that the index of the counter array is 1 greater than the ascii value of the character
	// Type signature: (Word[],int) -> Word[]
	
	public Word[] countingSort(Word[] words, int d, int max) {
		int[] count = new int[27];
		Word[] sorted = new Word[words.length];
		for(int i = 0; i < words.length; i++) { // Runs in O(n)
			//The current digit/index varies between strings of different lengths
			int index = words[i].word.length() - max + d;
			if(index >= 0) {
				count[words[i].word.charAt(index) - 'a' + 1]++;
			} else {
				count[0]++;
			}
		}
		for(int i = 1; i < count.length; i++) { // Runs in O(96) = O(1)
			count[i] += count[i-1];
		}
		for(int i = words.length - 1; i >= 0; i--) { // Runs in O(n)
			//The digit/index varies between strings of different lengths
			int index = words[i].word.length() - max + d;
			if(index >= 0) { 
				sorted[count[words[i].word.charAt(index) - 'a' + 1] - 1] = words[i];
				count[words[i].word.charAt(index) - 'a' + 1]--;
			} else {
				sorted[count[0] - 1] = words[i];
				count[0]--;
			}
		}
		return sorted;
	}

	// A method that takes in a Word array and loop through it
	// The method would add the words in the same anagram class into an ArrayList
	// If the next word is not in the same anagram class, the method would add the
	// ArrayList to the final ArrayList and start a new ArrayList
	// Type signature: (Word[]) -> ArrayList<ArrayList<String>>
	public ArrayList<ArrayList<String>> group(Word[] words) { 
		ArrayList<ArrayList<String>> anagrams = new ArrayList<ArrayList<String>>();
		ArrayList<String> anagram = new ArrayList<String>();
		anagram.add(dictionary.get(words[0].index));
		for (int i = 1; i < words.length; i++) { // Runs in O(n)
			if (words[i].word.equals(words[i - 1].word)) {	//Runtime O(k)
				anagram.add(dictionary.get(words[i].index));
			} else {
				anagrams.add(anagram);
				anagram = new ArrayList<String>();
				anagram.add(dictionary.get(words[i].index));
			}
		}
		anagrams.add(anagram);
		return anagrams;
	}
}