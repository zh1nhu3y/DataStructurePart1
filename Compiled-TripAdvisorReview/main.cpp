/**
 *  main.cpp
 */

#include <iostream>
#include <chrono>
#include "ReviewContainer.h"
#include "WordArray.h"
// #include "SentimentAnalysis.h"
#include "SummaryReportGenerator.h"
#include "ArrayOperation.h"
#include "sentimentComparison.h"

using namespace std;
using namespace std::chrono;

void displayMainMenu() {
    cout << "\n ================== MENU ===================\n\n";
    cout << "1. Clean Data" << endl;
    cout << "2. Display Positive Words" << endl;
    cout << "3. Display Negative Words" << endl;
    cout << "4. Display Reviews" << endl;
    cout << "5. Sentiment Analysis" << endl;
    cout << "6. Compare Sentiment Score with Rating" << endl;
    cout << "7. Generate Summary Report" << endl;
    cout << "\n0. Exit" << endl;
}

void displayPositiveWordsMenu(WordArray& positiveWords, ArrayOperation& operations, SentimentLinkedList& sentimentList) {
    int subchoice;
    do {
        cout << "========================================================================"<<endl;
        cout << "1. Display all Positive Words" << endl;
        cout << "2. Search Positive Word" <<    endl;
        cout << "\n0. Back to previous menu." << endl;
        cout << "\n\n Please enter your choice: ";
        cin >> subchoice;

        switch (subchoice) {
            case 1:
                positiveWords.displayWords();
                break;
            case 2: 
            {
                std::string searchWord;
                cout << "Enter the word you want to search: ";
                cin >> searchWord;
                cout << "Start Searching..." << endl;
                int wordIndex = operations.binarySearchWord(positiveWords, searchWord, 0, positiveWords.getWordCount() - 1);
                if (wordIndex != -1) {
                    cout << "Word found at index: " << wordIndex << endl;
                } else {
                    cout << "Word not found." << endl;
                }

                int linkedListIndex = sentimentList.binarySearchSentiment(positiveWords, searchWord);
                if (linkedListIndex != -1) {
                    cout << "Word found in linked list at index: " << linkedListIndex << endl;
                } else {
                    cout << "Word not found in linked list." << endl;
                }
                break;
            }
            case 0:
                return;  // Back to previous menu
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (subchoice != 0);
}

void displayNegativeWordsMenu(WordArray& negativeWords, ArrayOperation& operations, SentimentLinkedList& sentimentList) {
    int subchoice;
    do {
        cout << "========================================================================"<<endl;
        cout << "1. Display all Negative Words" << endl;
        cout << "2. Search Negative Word" << endl;
        cout << "\n0. Back to previous menu." << endl;
        cout << "\n\n Please enter your choice: ";
        cin >> subchoice;

        switch (subchoice) {
            case 1:
                negativeWords.displayWords();
                break;
            case 2: {
                std::string searchWord;
                cout << "Enter the word you want to search: ";
                cin >> searchWord;
                cout << "Start Searching..."<<endl;
                int wordIndex = operations.binarySearchWord(negativeWords, searchWord, 0, negativeWords.getWordCount() - 1);
                if (wordIndex != -1) {
                    cout << "Word found in array at index: " << wordIndex << endl;
                } else {
                    cout << "Word not found." << endl;
                }

                int linkedListIndex = sentimentList.binarySearchSentiment(negativeWords, searchWord);
                if (linkedListIndex != -1) {
                    cout << "Word found in linked list at index: " << linkedListIndex << endl;
                } else {
                    cout << "Word not found in linked list." << endl;
                }
                break;
            }
            case 0:
                return;  // Back to previous menu
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (subchoice != 0);
}

void displayReviewMenu(CustomArray& reviews, ArrayOperation& operations,SentimentLinkedList& sentimentList) {
    int subchoice;
    do {
        cout << "========================================================================"<<endl;
        cout << "1. Display all Reviews" << endl;
        cout << "2. Display all Reviews in Table." << endl;
        cout << "3. Sort Reviews By Ratings." << endl;
        cout << "4. Display Reviews by Rating." << endl;
        cout << "\n0. Back to previous menu." << endl;
        cout << "\n\n Please enter your choice: ";

        cin >> subchoice;

        switch (subchoice) {
            case 1:
                operations.displayReviews(reviews);
                break;
            case 2:
                operations.displayReviewsTable(reviews);
                break;
            case 3: {
                sentimentList.clear();  
                
                // Add each review to the linked list
                for (int i = 0; i < reviews.getSize(); i++) {
                    std::string reviewText = reviews.getReview(i);
                    int reviewRating = reviews.getRating(i);
                    sentimentList.insertAtEnd(reviewText, reviewRating);
                }
                cout << "Number of reviews loaded to list: " << sentimentList.getSize() << endl; // print number of reviews loaded

                cout << "Start Sorting ..."<<endl;
                auto astart = high_resolution_clock::now();
                operations.quickSort(reviews, 0, reviews.getSize() - 1);
                auto astop = high_resolution_clock::now();
                duration<double> aduration = duration_cast<milliseconds>(astop - astart);
                cout << "Array Quick Sort Time: " << aduration.count() << " seconds" << endl;

                SentimentNode* head = sentimentList.getHead();
                SentimentNode* low = head;
                SentimentNode* high = nullptr;

                // Find the tail node (last node in the list)
                if (head != nullptr) {
                    SentimentNode* current = head;
                    while (current->next != nullptr) {
                        current = current->next;
                    }
                    high = current;
                }

                if (low != nullptr && high != nullptr) {
                    auto bstart = high_resolution_clock::now();
                    sentimentList.quickSort(head, low, high);
                    auto bstop = high_resolution_clock::now();
                    duration<double> bduration = duration_cast<milliseconds>(bstop - bstart);
                    cout << "Linked List Quick Sort Time: " << bduration.count() << " seconds" << endl;
                    cout << "Done Sorting" << endl;
                } else {
                    cout << "Error: Linked list is empty or pointers are null!" << endl;
                }
                    // ========= Bubble Sort ============
                    reviews.clear();  // Clear the list
                    sentimentList.clear();  // Clear the list
                    cleanCSV("C:\\Users\\jason\\OneDrive - Asia Pacific University\\DEGREE APD2F2402\\YEAR 2 SEM 2\\DSTR\\Assignment\\tripadvisor_hotel_reviews.csv", reviews);  // Load data from CSV file
                    
                    
                    for (int i = 0; i < reviews.getSize(); i++) {
                        std::string reviewText = reviews.getReview(i);
                        int reviewRating = reviews.getRating(i);
                        sentimentList.insertAtEnd(reviewText, reviewRating);  // Re-insert unsorted data
                    }

                    cout << "Start Sorting with Bubble Sort..." << endl;
                    operations.bubbleSortArray(reviews);  
                    

                    
                    auto dstart = high_resolution_clock::now();
                    sentimentList.bubbleSortLinkedList();  
                    auto dstop = high_resolution_clock::now();
                    duration<double> dduration = duration_cast<microseconds>(dstop - dstart);
                    cout << "Linked List Bubble Sort Time: " << dduration.count() << " microseconds" << endl;
                    cout << "Done Sorting with Bubble Sort." << endl;
                    
                
                break;
            }

            case 4: {
                int searchRating;
                int resultCountArrayBinary = 0, resultCountLLBinary = 0;
                int resultCountArrayLinear = 0, resultCountLLLinear = 0;

                // Input Rating
                cout << "Enter the rating you want to display: ";
                cin >> searchRating;

                cout << "Start searching..." << endl;

                // Binary Search on Array
                auto arrstart = high_resolution_clock::now(); 
                int* indicesBinaryArray = operations.binarySearchAll(reviews, searchRating, resultCountArrayBinary);
                operations.displaySearchedReviews(reviews, indicesBinaryArray, resultCountArrayBinary);
                auto arrstop = high_resolution_clock::now();
                duration<double> arrduration = duration_cast<microseconds>(arrstop - arrstart);

                // Binary Search on Linked List (inefficient but for comparison purposes)
                auto llstart = high_resolution_clock::now(); 
                int* indicesBinaryLL = sentimentList.binarySearchAllLinkedList(sentimentList, searchRating, resultCountLLBinary);
                sentimentList.displaySearchedReviews(searchRating);
                auto llstop = high_resolution_clock::now();
                duration<double> llduration = duration_cast<microseconds>(llstop - llstart);
                
                // Linear Search on Array
                auto arrlnstart = high_resolution_clock::now(); 
                int* indicesLinearArray = operations.linearSearchAll(reviews, searchRating, resultCountArrayLinear);
                operations.displaySearchedReviews(reviews, indicesBinaryLL, resultCountArrayLinear);
                auto arrlnstop = high_resolution_clock::now();
                duration<double> arrlnduration = duration_cast<microseconds>(arrlnstop - arrlnstart);

                // Linear Search on Linked List
                auto lllnstart = high_resolution_clock::now(); 
                int* indicesLinearLL = sentimentList.linearSearchAll(sentimentList.getHead(), searchRating, resultCountLLLinear);
                sentimentList.displaySearchedReviews(searchRating);
                auto lllnstop = high_resolution_clock::now();
                duration<double> lllnduration = duration_cast<microseconds>(lllnstop - lllnstart);

                // Display results for each search method
                operations.displaySearchedReviews(reviews, indicesBinaryArray, resultCountArrayBinary);
                
                cout << "Done searching!" << endl;
                cout << "Array Binary Search Time: " << arrduration.count() << " microseconds" << endl;
                cout << "Linked List Binary Search Time: " << llduration.count() << " microseconds" << endl;
                cout << "Array Linear Search Time: " << arrlnduration.count() << " microseconds" << endl;
                cout << "Linked List Linear Search Time: " << lllnduration.count() << " microseconds" << endl;

                // Cleanup dynamically allocated memory
                delete[] indicesBinaryArray;
                delete[] indicesBinaryLL;
                delete[] indicesLinearArray;
                delete[] indicesLinearLL;

                break;
            }

            case 0:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }

    } while (subchoice != 0);
}

int main()
{
    cout << "\n DATA STRUCTURE PART 1 - GROUP M";
    cout << "\n Pan Zhin Huey, Law Mei Jun, Jason Soo Zi Shen, Lee Cen Yu\n";
    cout << "\n\n================= DATA STORAGE ================\n\n";

    // Initialize the Array Opretions
    ArrayOperation operations;

    // Jason Input file path
    std::string inputFile = "C:\\Users\\jason\\OneDrive - Asia Pacific University\\DEGREE APD2F2402\\YEAR 2 SEM 2\\DSTR\\Assignment\\tripadvisor_hotel_reviews.csv";
    std::string outputFile = "C:\\Users\\jason\\OneDrive - Asia Pacific University\\DEGREE APD2F2402\\YEAR 2 SEM 2\\DSTR\\Assignment\\cleaned_tripadvisor_hotel_reviews.csv";

    // MJ Input file path
    // std::string inputFile = "C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/tripadvisor_hotel_reviews.csv";
    // std::string outputFile = "C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/cleaned_tripadvisor_hotel_reviews.csv";

    // Huey File path
    // std::string inputFile = "C:/Users/Zhin Huey/OneDrive - Asia Pacific University/Degree Year2-SEM2/Data Structure/Assignement 1/tripadvisor_hotel_reviews.csv";
    // std::string outputFile = "C:/Users/Zhin Huey/OneDrive - Asia Pacific University/Degree Year2-SEM2/Data Structure/Assignement 1/organized_hotel_reviews.csv";

    
    // Initialize custom array with a starting capacity
    CustomArray reviews(25000);

    // store positive words, negative words into array
    WordArray positiveWords, negativeWords;
    positiveWords.loadWordsFromFile("C:\\Users\\jason\\OneDrive - Asia Pacific University\\DEGREE APD2F2402\\YEAR 2 SEM 2\\DSTR\\Assignment\\positive-words.txt");
    negativeWords.loadWordsFromFile("C:\\Users\\jason\\OneDrive - Asia Pacific University\\DEGREE APD2F2402\\YEAR 2 SEM 2\\DSTR\\Assignment\\negative-words.txt");

    // Create a SentimentLinkedList to analyze the reviews
    SentimentLinkedList sentimentList(positiveWords, negativeWords);

    int choice;

    do {
        displayMainMenu();
        cout << "\n\n Please enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Clean the CSV file and store the data
                cleanCSV(inputFile, reviews);
                cout << "Saving into file ..."<<endl;
                // Output cleaned reviews and ratings to a new CSV file
                reviews.writeToFile(outputFile);
                cout << "File saved!"<<endl;
                break;
            case 2:
                displayPositiveWordsMenu(positiveWords, operations, sentimentList);
                break;
            case 3:
                displayNegativeWordsMenu(negativeWords, operations, sentimentList);
                break;
            case 4:
                displayReviewMenu(reviews, operations, sentimentList);
                break;

            case 5:
                {
                    cout << "========================= Sentiment Analysis ==========================\n\n" << endl;

                    cout << "Start Sentiment Analyzing..." << endl;
                    sentimentList.clear();
                    // Add each reviews to the linked list
                    for (int i = 0; i < reviews.getSize(); i++)
                    {
                        std::string reviewText = reviews.getReview(i);
                        int reviewRating = reviews.getRating(i);
                        sentimentList.insertAtEnd(reviewText, reviewRating);
                    }
                    cout << "Number of reviews loaded to list: " << sentimentList.getSize() << endl; // print number of reviews loaded

                    auto asstart = high_resolution_clock::now();
                    // Sentiment Analysis for all reviews
                    sentimentList.analyzeSentiment();  // <-- Calls the analyzeSentiment function
                    auto asend = high_resolution_clock::now();

                    sentimentList.bubbleSortSentiment();
                    // sentimentList.displaySentimentAnalysisResults();
                    duration<double> aduration = duration_cast<microseconds>(asend - asstart) ;

                    cout << "Sentiment Analysis Completed!" << endl;
                    cout << "Time taken: " << aduration.count() << " microseconds" << endl;

                    // Save sentiment analysis results to a file
                    cout << "Saving into File..." << endl;
                    sentimentList.saveResultsToFile("sentiment_analysis_results.txt");
                    cout << "File Saved!" << endl;
                    

                    break;
                }

            case 6:
            {
                // Compare Sentiment Analysis with Rating
                cout << "\n================= SENTIMENT COMPARISON ================\n\n";

                // Create an instance of SentimentComparison
                SentimentComparison sentimentComparison;

                // Compare sentiment scores with given ratings
                cout << "Start Sentiment Score Comparing..." << endl;
                auto estart = std::chrono::high_resolution_clock::now();
                sentimentComparison.compareSentimentAndRating(sentimentList);
                auto eend = std::chrono::high_resolution_clock::now();
                duration<double> eduration = duration_cast<milliseconds>(eend - estart) ;
                cout << "Comparison Done!" << endl;
                cout << "Comparison Time: " << eduration.count() << " milliseconds" << endl;

                // Save sentiment analysis results to a file
                cout << "Saving into File..." << endl;
                sentimentComparison.saveComparisonToFile(sentimentList, "sentiment_comparison_results.txt"); // Save to file
                cout << "File Saved!" << endl;
                break;
            }
            case 7:
            {
                // Code for generating summary report
                 cout << "\n================= SUMMARY REPORT ================\n\n";

                // Create report generator using existing word arrays
                SummaryReportGenerator reportGenerator(positiveWords, negativeWords);

                // Convert array to linked list and analyze reviews
                cout << "Start Analyzing Review..." << endl;
                auto fstart = std::chrono::high_resolution_clock::now();
                reportGenerator.analyzeReviews(reviews); // uses the already cleaned reviews
                auto fend = std::chrono::high_resolution_clock::now();
                duration<double> fduration = duration_cast<milliseconds>(fend - fstart) / 1000;
                cout << "Review Analyzing Done!" << endl;
                cout << "Analyze Review Time: " << fduration.count() << " seconds" << endl;


                // Generate comprehensive report
                cout << "Start Generating Report..." << endl;
                auto gstart = std::chrono::high_resolution_clock::now();
                reportGenerator.generateEnhancedReport("summary_report.txt"); // change to your own path
                auto gend = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> grduration = duration_cast<microseconds>(gend - gstart) ;
                cout << "Report Generated!" << endl;
                cout << "Generating Report Time: " << grduration.count() << " microseconds" << endl;
                break;
            }
            case 0:{
                cout << "Exiting the program. Goodbye!" << endl;
                cout << "Have a nice day!" << endl;
                break;}
            default:
                {cout << "Invalid choice. Please try again.\n";}
        }
    } while (choice != 0);

    // MJ File path
    // positiveWords.loadWordsFromFile("C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/positive-words.txt");
    // negativeWords.loadWordsFromFile("C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/negative-words.txt");

    // Huey File path
    // positiveWords.loadWordsFromFile("C:/Users/Zhin Huey/OneDrive - Asia Pacific University/Degree Year2-SEM2/Data Structure/Assignement 1/positive-words.txt");
    // negativeWords.loadWordsFromFile("C:/Users/Zhin Huey/OneDrive - Asia Pacific University/Degree Year2-SEM2/Data Structure/Assignement 1/negative-words.txt");


   
    cout << "\n================= END OF PROGRAM =================\n\n";
    return 0;
}
