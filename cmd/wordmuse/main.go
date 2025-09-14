package main

import (
	"fmt"
	"os"

	"apimodule/muse" // <-- ensure this matches your go.mod module name
)

func main() {
	if len(os.Args) != 2 {
		fmt.Fprintln(os.Stderr, "usage: wordmuse <word>")
		os.Exit(2)
	}
	word := os.Args[1]

	client := &muse.Client{URL: "https://api.datamuse.com"}

	items, err := client.ListItems(word)
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}

	// Helpful visibility: count and each item
	fmt.Fprintf(os.Stderr, "Fetched %d items for %q\n", len(items), word)
	for i, it := range items {
    	fmt.Printf("%d. %s\n", i+1, it.Word)
	}

}
