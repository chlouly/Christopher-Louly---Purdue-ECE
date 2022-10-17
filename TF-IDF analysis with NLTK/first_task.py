from opcode import hasjabs


def get_formatted_text(filename) :
    
    text = open(filename, 'r')

    try:
        lines = text.readlines()
        lines = [('__' + x.rstrip('\n ').lower() + '__') for x in lines]
    finally:
        text.close()

    return lines
        
        

#Arguments:
#  line: a string of text
#   n : Length of each n-gram
#Returns: a list of n-grams
#Notes: make sure to pad the beginning and end of the string with '_'
#       make sure to convert the string to lower-case
#       so "Hello" should be turned into "__hello__" before processing
def get_ngrams(line, n) :
    ngrams = []
    nset = set([])

    for x in range(len(line) - n + 1):
        nset.add(line[x : x + n])

    ngrams = list(nset)

    return ngrams



#Arguments:
#  filename: the filename to create an n-gram dictionary for
#   n : Length of each n-gram
#Returns: a dictionary, with ngrams as keys, and frequency of that ngram as the value.
def get_dict(filename, n):
    ngram_dict = {}

    lines = get_formatted_text(filename)
    list_ngrams = [get_ngrams(x, n) for x in lines]
    newList = []
    for i in list_ngrams:
        newList += i

    ngram_dict = dict.fromkeys(list(set(newList)), 0)

    for line in lines:
        for i in range(len(line) - n + 1):
            ngram_dict[line[i: i + n]] += 1
            
    return ngram_dict



#Arguments:
#   filename: the filename to generate a list of top N (most frequent n-gram, count) tuples for
#   N: the number of most frequent n-gram tuples to have in the output list.
#   n : Length of each n-gram
#Returns: a list of N tuples representing the (n-gram, count) pairs that are most common in the file. 
def top_N_common(filename,N,n):
    common_N = []    
    ngrams = get_dict(filename, n)
    #Sort the dictioary
    ngrams = {k: v for k, v in sorted(ngrams.items(), key = lambda item: item[0])}
    ngrams = {k: v for k, v in sorted(ngrams.items(), key = lambda item: item[1])}

    for _ in range(N):
        common_N.append(ngrams.popitem())

    return common_N



#Arguments:
#   filename_list: a list of filepath strings for the different language text files to process
#   n : Length of each n-gram
#Returns: a list of dictionaries where there is a dictionary for each language file processed. 
def get_all_dicts(filename_list,n):
    lang_dicts = []

    for path in filename_list:
        lang_dicts.append(get_dict(path, n))

    return lang_dicts



#Arguments:
#   listOfDicts: A list of dictionaries where the keys are n-grams and the values are the count of the n-gram
#Returns an alphabetically sorted list containing all of the n-grams across all of the dictionaries in listOfDicts (note, do not have duplicates n-grams)
def dict_union(listOfDicts):
    union_ngrams = []
    listOflists = [[item[0] for item in dictionary.items()] for dictionary in listOfDicts]
    
    for list_ in listOflists:
        union_ngrams += list_

    union_ngrams = sorted(list(set(union_ngrams)))

    return union_ngrams



#Arguments:
#   langFiles: list of filepaths of the languages to compare test_file to.
#   n : Length of each n-gram
#Returns a list of all the n-grams across the six languages
def get_all_ngrams(langFiles,n):
    all_ngrams = dict_union(get_all_dicts(langFiles, n))

    return all_ngrams



#Arguments:
#   test_file: mystery file's filepath to determine language of
#   langFiles: list of filepaths of the languages to compare test_file to.
#   N: the number of top n-grams for comparison
#   n : length of n-gram
# Return a Tuple which is of the format (filename1, filename2, similarity_score), where similarity_score is the score between filename_1 and filename_2
def compare_langs(langFiles,N,n):
    topN = []   #list of ngram sets corresponding to 'langFiles'

    for lang in langFiles:
        ngrams = top_N_common(lang, N, n)
        set_ = set(map(lambda item: item[0], ngrams))
        topN.append(set_)

    best_comb = 0

    for i in range(len(topN) - 1):
        for j in range(i + 1 ,len(topN)):
            val = len(topN[i].intersection(topN[j])) / N
            if val > best_comb:
                best_comb = val
                most_similar_pair = (langFiles[i], langFiles[j], val)
    
    return most_similar_pair



if __name__ == '__main__':
    from os import listdir
    from os.path import isfile, join, splitext
    
    #Test top10Common()
    path = join('ngrams','english.txt')
    print(top_N_common(path,10,3))
    
    #Compile ngrams across all 6 languages and find the two most similar languages and their similarity score for various n-gram lengths 

    path='ngrams'
    file_list = [f for f in listdir(path) if isfile(join(path, f))]
    path_list = [join(path, f) for f in file_list]

    for n in range(3,6):
        print(get_all_ngrams(path_list,n)) #list of all n-grams spanning all languages
    
    for n in range(3,6):
        print(compare_langs(path_list, 1000,n)) #Find the similarity between languages
    
