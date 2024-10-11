auto llstart = high_resolution_clock::now();
            int *indicesBinaryLL = sentimentList.binarySearchAllLinkedList(sentimentList, searchRating, resultCountLLBinary);
            sentimentList.displaySearchedReviews(searchRating);
            auto llstop = high_resolution_clock::now();
            // duration<double> llduration = duration_cast<microseconds>(llstop - llstart);
            duration<double, milli> llduration = llstop - llstart;