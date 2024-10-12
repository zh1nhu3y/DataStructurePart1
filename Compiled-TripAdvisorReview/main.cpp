/**
 *  main.cpp
 */

#include <iostream>
#include <chrono>
#include "ReviewContainer.h"
#include "WordArray.h"
#include "linkedlist.h"
#include "SentimentAnalysis.h"
#include "SummaryReportGenerator.h"
#include "ArrayOperation.h"
// #include "sentimentComparison.h"

using namespace std;
using namespace std::chrono;

void displayMainMenu()
{
    cout << "\n ================== MENU ===================\n\n";
    cout << "1. Display Positive Words" << endl;
    cout << "2. Display Negative Words" << endl;
    cout << "3. Display and Sort Reviews" << endl;
    cout << "4. Sentiment Analysis" << endl;
    cout << "5. Compare Sentiment Score with Rating" << endl;
    cout << "6. Generate Summary Report" << endl;
    cout << "\n0. Exit" << endl;
}

void displayPositiveWordsMenu(WordArray &positiveWords, ArrayOperation &operations, SentimentLinkedList &sentimentList)
{
    int subchoice;
    do
    {
        cout << "========================================================================" << endl;
        cout << "1. Display all Positive Words" << endl;
        cout << "2. Search Positive Word" << endl;
        cout << "\n0. Back to previous menu." << endl;
        cout << "\n\n Please enter your choice: ";
        cin >> subchoice;

        switch (subchoice)
        {
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
            if (wordIndex != -1)
            {
                cout << "Word found at index: " << wordIndex << endl;
            }
            else
            {
                cout << "Word not found." << endl;
            }

            int linkedListIndex = sentimentList.binarySearchSentiment(positiveWords, searchWord);
            if (linkedListIndex != -1)
            {
                cout << "Word found in linked list at index: " << linkedListIndex << endl;
            }
            else
            {
                cout << "Word not found in linked list." << endl;
            }
            break;
        }
        case 0:
            return; // Back to previous menu
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (subchoice != 0);
}

void displayNegativeWordsMenu(WordArray &negativeWords, ArrayOperation &operations, SentimentLinkedList &sentimentList)
{
    int subchoice;
    do
    {
        cout << "========================================================================" << endl;
        cout << "1. Display all Negative Words" << endl;
        cout << "2. Search Negative Word" << endl;
        cout << "\n0. Back to previous menu." << endl;
        cout << "\n\n Please enter your choice: ";
        cin >> subchoice;

        switch (subchoice)
        {
        case 1:
            negativeWords.displayWords();
            break;
        case 2:
        {
            std::string searchWord;
            cout << "Enter the word you want to search: ";
            cin >> searchWord;
            cout << "Start Searching..." << endl;
            int wordIndex = operations.binarySearchWord(negativeWords, searchWord, 0, negativeWords.getWordCount() - 1);
            if (wordIndex != -1)
            {
                cout << "Word found in array at index: " << wordIndex << endl;
            }
            else
            {
                cout << "Word not found." << endl;
            }

            int linkedListIndex = sentimentList.binarySearchSentiment(negativeWords, searchWord);
            if (linkedListIndex != -1)
            {
                cout << "Word found in linked list at index: " << linkedListIndex << endl;
            }
            else
            {
                cout << "Word not found in linked list." << endl;
            }
            break;
        }
        case 0:
            return; // Back to previous menu
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (subchoice != 0);
}

void displayReviewMenu(CustomArray &reviews, ArrayOperation &operations, SentimentLinkedList &sentimentList)
{
    int subchoice;
    do
    {
        cout << "========================================================================" << endl;
        cout << "1. Display all Reviews" << endl;
        cout << "2. Display all Reviews in Table." << endl;
        cout << "3. Sort Reviews By Ratings." << endl;
        cout << "4. Display Reviews by Rating." << endl;
        cout << "\n0. Back to previous menu." << endl;
        cout << "\n\n Please enter your choice: ";

        cin >> subchoice;

        switch (subchoice)
        {
        case 1:
            operations.displayReviews(reviews);
            break;
        case 2:
            operations.displayReviewsTable(reviews);
            break;
        case 3:
        {
            reviews.clear();                                                                                                                                            // Clear the list
            sentimentList.clear();                                                                                                                                      // Clear the list
            cleanCSV("C:\\Users\\jason\\OneDrive - Asia Pacific University\\DEGREE APD2F2402\\YEAR 2 SEM 2\\DSTR\\Assignment\\tripadvisor_hotel_reviews.csv", reviews); // Load data from CSV file

            for (int i = 0; i < reviews.getSize(); i++)
            {
                std::string reviewText = reviews.getReview(i);
                int reviewRating = reviews.getRating(i);
                sentimentList.insertAtEnd(reviewText, reviewRating); // Re-insert unsorted data
            }
            
            cout << "Number of reviews loaded to Linked list: " << sentimentList.getSize() << endl; // print number of reviews loaded

            cout << "Start Sorting ..." << endl;
            auto astart = high_resolution_clock::now();
            operations.quickSort(reviews, 0, reviews.getSize() - 1);
            auto astop = high_resolution_clock::now();
            duration<double, milli> aduration = astop - astart;
            cout << "Array Quick Sort Time: " << aduration.count() << " milliseconds" << endl;
            // operations.displayReviewsTable(reviews);

            SentimentNode *head = sentimentList.getHead();
            SentimentNode *low = head;
            SentimentNode *high = nullptr;

            // Find the tail node (last node in the list)
            if (head != nullptr)
            {
                SentimentNode *current = head;
                while (current->next != nullptr)
                {
                    current = current->next;
                }
                high = current;
            }

            if (low != nullptr && high != nullptr)
            {
                auto bstart = high_resolution_clock::now();
                sentimentList.quickSort(head, low, high);
                auto bstop = high_resolution_clock::now();
                // duration<double> bduration = duration_cast<milliseconds>(bstop - bstart);
                duration<double, milli> bduration = bstop - bstart;
                cout << "Linked List Quick Sort Time: " << bduration.count() << " milliseconds" << endl;
                cout << "Done Sorting" << endl;
            }
            else
            {
                cout << "Error: Linked list is empty or pointers are null!" << endl;
            }
            // ========= Bubble Sort ============
            reviews.clear();                                                                                                                                            // Clear the list
            sentimentList.clear();                                                                                                                                      // Clear the list
            cleanCSV("C:\\Users\\jason\\OneDrive - Asia Pacific University\\DEGREE APD2F2402\\YEAR 2 SEM 2\\DSTR\\Assignment\\tripadvisor_hotel_reviews.csv", reviews); // Load data from CSV file

            for (int i = 0; i < reviews.getSize(); i++)
            {
                std::string reviewText = reviews.getReview(i);
                int reviewRating = reviews.getRating(i);
                sentimentList.insertAtEnd(reviewText, reviewRating); // Re-insert unsorted data
            }
            cout << "Number of reviews loaded to Linked list: " << sentimentList.getSize() << endl; // print number of reviews loaded
            cout << "Start Sorting with Bubble Sort..." << endl;
            auto cstart = high_resolution_clock::now();
            operations.bubbleSortArray(reviews);
            auto cend = high_resolution_clock::now();
            duration<double, milli> cduration = cend - cstart;
            std::cout << "Array Bubble Sort Time: " << cduration.count() << " milliseconds" << endl;

            auto dstart = high_resolution_clock::now();
            sentimentList.bubbleSortLinkedList();
            auto dstop = high_resolution_clock::now();
            // duration<double> dduration = duration_cast<microseconds>(dstop - dstart);
            duration<double, milli> dduration = dstop - dstart;
            std::cout << "Linked List Bubble Sort Time: " << dduration.count() << " milliseconds" << endl;
            std::cout << "Done Sorting with Bubble Sort." << endl;

            break;
        }

        case 4:
        {
            for (int i = 0; i < reviews.getSize(); i++)
            {
                std::string reviewText = reviews.getReview(i);
                int reviewRating = reviews.getRating(i);
                sentimentList.insertAtEnd(reviewText, reviewRating); // Re-insert unsorted data
            }

            int searchRating;
            int resultCountArrayBinary = 0, resultCountLLBinary = 0;
            int resultCountArrayLinear = 0, resultCountLLLinear = 0;

            int *indicesBinaryArray; 
            int *indicesBinaryLL; 
            int *indicesLinearArray; 
            int *indicesLinearLL; 
            // Input Rating
            std::cout << "Enter the rating you want to display: ";
            cin >> searchRating;

            std::cout << "Start searching..." << endl;
            // Binary Search for array
            auto arrstart = high_resolution_clock::now();  // Start timing
            // Run the binary search 10 times, but store the result only once
            for (int i = 0; i < 500; i++)
            {
                if (i == 499)  // On the final iteration, capture the result
                {
                    indicesBinaryArray = operations.binarySearchAll(reviews, searchRating, resultCountArrayBinary);
                }
                else  // Perform the search without storing the result
                {
                    int tempResultCount = 0;  // Temporary variable to discard the result count
                    int *tempIndices = operations.binarySearchAll(reviews, searchRating, tempResultCount);
                    delete[] tempIndices;  // Clean up the temporary result array if dynamically allocated
                }
            }
            auto arrstop = high_resolution_clock::now();  // Stop timing
            duration<double, micro> arrduration = arrstop - arrstart;
            // Display the search result (only executed once)
            //operations.displaySearchedReviews(reviews, indicesBinaryArray, resultCountArrayBinary);


            // Binary Search on Linked List (inefficient but for comparison purposes)
            auto llstart = high_resolution_clock::now();
            // Run the binary search 10 times, but store the result only once
            for (int i = 0; i < 500; i++)
            {
                if (i == 499)  // On the final iteration, capture the result
                {
                    indicesBinaryLL = sentimentList.binarySearchAllLinkedList(sentimentList, searchRating, resultCountLLBinary);
                }
                else  // Perform the search without storing the result
                {
                    int tempResultCount = 0;  // Temporary variable to discard the result count
                    int *tempIndices = sentimentList.binarySearchAllLinkedList(sentimentList, searchRating, resultCountLLBinary);
                    delete[] tempIndices;  // Clean up the temporary result array
            }
            }
            auto llstop = high_resolution_clock::now();
            duration<double, milli> llduration = llstop - llstart;
            // sentimentList.displaySearchedReviews(searchRating);

            // Linear Search on Array
            auto arrlnstart = high_resolution_clock::now();
            for (int i = 0; i < 500; i++)
            {
                if (i == 499)  // On the final iteration, capture the result
                {
                    indicesLinearArray = operations.linearSearchAll(reviews, searchRating, resultCountArrayLinear);
                }
                else  // Perform the search without storing the result
                {
                    int tempResultCount = 0;  // Temporary variable to discard the result count
                    int *tempIndices = operations.linearSearchAll(reviews, searchRating, resultCountArrayLinear);
                    delete[] tempIndices;  // Clean up the temporary result array
                }
            }
            auto arrlnstop = high_resolution_clock::now();
            duration<double, micro> arrlnduration = arrlnstop - arrlnstart;
            // operations.displaySearchedReviews(reviews, indicesBinaryLL, resultCountArrayLinear);

            // Linear Search on Linked List
            auto lllnstart = high_resolution_clock::now();
            for (int i = 0; i < 500; i++)
            {
                if (i == 499)  // On the final iteration, capture the result
                {
                    indicesLinearLL = sentimentList.linearSearchAll(sentimentList.getHead(), searchRating, resultCountLLLinear);
                }
                else  // Perform the search without storing the result
                {
                    int tempResultCount = 0;  // Temporary variable to discard the result count
                    int *tempIndices = sentimentList.linearSearchAll(sentimentList.getHead(), searchRating, resultCountLLLinear);
                    delete[] tempIndices;  // Clean up the temporary result array
                }
            }
            auto lllnstop = high_resolution_clock::now();
            duration<double, micro> lllnduration = lllnstop - lllnstart;
            // sentimentList.displaySearchedReviews(searchRating);

            // Display results for each search method
            operations.displaySearchedReviews(reviews, indicesBinaryArray, resultCountArrayBinary);

            std::cout << "Done searching!" << endl;
            std::cout << "Array Binary Search Time (500 Times): " << arrduration.count() << " microseconds" << endl;
            std::cout << "Linked List Binary Search Time (500 Times): " << llduration.count() << " milliseconds" << endl;
            std::cout << "Array Linear Search Time (500 Times): " << arrlnduration.count() << " microseconds" << endl;
            std::cout << "Linked List Linear Search Time (500 Times): " << lllnduration.count() << " microseconds" << endl;

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
        
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }

    } while (subchoice != 0);
    };


int main()
{
    std::cout << "\n DATA STRUCTURE PART 1 - GROUP M";
    std::cout << "\n Pan Zhin Huey, Law Mei Jun, Jason Soo Zi Shen, Lee Cen Yu\n";
    std::cout << "\n\n================= DATA STORAGE ================\n\n";

    // Initialize the Array Opretions
    ArrayOperation operations;
    WordArray positiveWords, negativeWords; 
    // Jason Input file path
    std::string inputFile = "C:\\Users\\jason\\OneDrive - Asia Pacific University\\DEGREE APD2F2402\\YEAR 2 SEM 2\\DSTR\\Assignment\\tripadvisor_hotel_reviews.csv";
    std::string outputFile = "C:\\Users\\jason\\OneDrive - Asia Pacific University\\DEGREE APD2F2402\\YEAR 2 SEM 2\\DSTR\\Assignment\\cleaned_tripadvisor_hotel_reviews.csv";
    positiveWords.loadWordsFromFile("C:\\Users\\jason\\OneDrive - Asia Pacific University\\DEGREE APD2F2402\\YEAR 2 SEM 2\\DSTR\\Assignment\\positive-words.txt");
    negativeWords.loadWordsFromFile("C:\\Users\\jason\\OneDrive - Asia Pacific University\\DEGREE APD2F2402\\YEAR 2 SEM 2\\DSTR\\Assignment\\negative-words.txt");
    
    // MJ File path
    // positiveWords.loadWordsFromFile("C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/positive-words.txt");
    // negativeWords.loadWordsFromFile("C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/negative-words.txt");
    // std::string inputFile = "C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/tripadvisor_hotel_reviews.csv";
    // std::string outputFile = "C:/Users/lawme/OneDrive - Asia Pacific University/Degree/Sem 2/Data Structure/Assignment/DSTR_P1_Data/cleaned_tripadvisor_hotel_reviews.csv";

    // Huey File path
    // positiveWords.loadWordsFromFile("C:/Users/Zhin Huey/OneDrive - Asia Pacific University/Degree Year2-SEM2/Data Structure/Assignement 1/positive-words.txt");
    // negativeWords.loadWordsFromFile("C:/Users/Zhin Huey/OneDrive - Asia Pacific University/Degree Year2-SEM2/Data Structure/Assignement 1/negative-words.txt");
    // std::string inputFile = "C:/Users/Zhin Huey/OneDrive - Asia Pacific University/Degree Year2-SEM2/Data Structure/Assignement 1/tripadvisor_hotel_reviews.csv";
    // std::string outputFile = "C:/Users/Zhin Huey/OneDrive - Asia Pacific University/Degree Year2-SEM2/Data Structure/Assignement 1/organized_hotel_reviews.csv";
  
    // Initialize custom array with a starting capacity
    CustomArray reviews(25000);

     // Clean the CSV file and store the data
    // auto cleanstart = high_resolution_clock::now();
    // cleanCSV(inputFile, reviews);
    // auto cleanend = high_resolution_clock::now();
    // duration<double, milli> cleanduration = cleanend - cleanstart;
    // cout << "Loading and Cleaning Data Completed!" << endl;
    // cout << "Time taken: " << cleanduration.count() << " milliseconds" << endl;

    // // cout << "Time taken: " << cleanduration.count() << " milliseconds" << endl;
    // operations.insertionSortArray(reviews);

    // // Output cleaned reviews and ratings to a new CSV file
    // cout << "Saving into File..." << endl;
    // reviews.writeToFile(outputFile);
    // cout << "File saved!" << endl;
    
    // Create a SentimentLinkedList to analyze the reviews
    SentimentLinkedList sentimentList(positiveWords, negativeWords);
    int choice;
    do
    {
        displayMainMenu();
        cout << "\n\n Please enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            displayPositiveWordsMenu(positiveWords, operations, sentimentList);
            break;
        case 2:
            displayNegativeWordsMenu(negativeWords, operations, sentimentList);
            break;
        case 3:
            displayReviewMenu(reviews, operations, sentimentList);
            break;

        case 4:
        {
            cout << "========================= Sentiment Analysis ==========================\n\n"
                 << endl;

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

            // sentimentList.displaySentimentAnalysisResults();
            // duration<double> aduration = duration_cast<microseconds>(asend - asstart) ;
            duration<double, milli> aduration = asend - asstart;
            cout << "Sentiment Analysis Completed!" << endl;
            cout << "Time taken for Sentiment Analysis: " << aduration.count() << " milliseconds" << endl;

            auto bubblestart = high_resolution_clock::now();
            sentimentList.bubbleSortSentiment();
            auto bubbleend = high_resolution_clock::now();
            duration<double, milli> bubbleduration = bubbleend - bubblestart;
            cout << "Time taken for Bubble Sort: " << bubbleduration.count() << " milliseconds" << endl;

            // Save sentiment analysis results to a file
            cout << "Saving into File..." << endl;
            sentimentList.saveResultsToFile("sentiment_analysis_results.txt");
            cout << "File Saved!" << endl;

            break;
        }

        case 5:
        {
            // Compare Sentiment Analysis with Rating
            cout << "\n================= SENTIMENT COMPARISON ================\n\n";


            // Compare sentiment scores with given ratings
            cout << "Start Sentiment Score Comparing..." << endl;
            auto estart = std::chrono::high_resolution_clock::now();
            sentimentList.saveComparisonToFile(sentimentList, "sentiment_comparison_results.txt"); // Save to file
            auto eend = std::chrono::high_resolution_clock::now();
            // duration<double> eduration = duration_cast<milliseconds>(eend - estart) ;
            duration<double, milli> eduration = eend - estart;
            cout << "Comparison Done!" << endl;
            cout << "Comparison Time: " << eduration.count() << " milliseconds" << endl;

            cout << "Output save to file!" << endl;
            // Save sentiment analysis results to a file
            
            break;
            }
            case 6:
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
            // duration<double> fduration = duration_cast<milliseconds>(fend - fstart) / 1000;
            duration<double, milli> fduration = fend - fstart;
            cout << "Review Analyzing Done!" << endl;
            cout << "Analyze Review Time: " << fduration.count() << " milliseconds" << endl;

            // Generate comprehensive report
            cout << "Start Generating Report..." << endl;
            auto gstart = std::chrono::high_resolution_clock::now();
            reportGenerator.generateEnhancedReport("summary_report.txt"); // change to your own path
            auto gend = std::chrono::high_resolution_clock::now();
            // std::chrono::duration<double> grduration = duration_cast<microseconds>(gend - gstart) ;
            duration<double, milli> grduration = gend - gstart;
            cout << "Report Generated!" << endl;
            cout << "Generating Report Time: " << grduration.count() << " milliseconds" << endl;
            break;
        }
        case 0:
        {
            cout << "Exiting the program. Goodbye!" << endl;
            cout << "Have a nice day!" << endl;
            break;
        }
        default:
        {
            cout << "Invalid choice. Please try again.\n";
        }
        }
    } while (choice != 0);
    cout << "\n================= END OF PROGRAM =================\n\n";
    return 0;
}
