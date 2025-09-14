package muse

import (
    "encoding/json"
    "fmt"
    "io"
    "net/http"
)

type Client struct {
    URL string
}

//takes a pointer to the client
func (c* Client) ListItems(term string) ([]*Item, error) {

    fullURL := c.URL + "/words?ml=" + term + "&max=5"
    //specifying the endpoint you want
    resp, err := http.Get(fullURL)
    if err != nil {
        return nil, fmt.Errorf("store: can't fetch inventory: %s", err)
    }
    //ensures we are closing the response body we opened with the get req
    defer resp.Body.Close()


    if resp.StatusCode != http.StatusOK { //this condition == failure
        //attempt to parse whats in the response body to provide more context to why fail
        msg, err := io.ReadAll(resp.Body)
        if err != nil {
            //return null, error message, and resp status, and error code
            return nil, fmt.Errorf("store: got non-OK response (%s). Can't read the body; %v", resp.Status, err)
        }
        //didnt work but got response, provide it msg 
        return nil, fmt.Errorf("store: got non-OK response(%s): %v", resp.Status, string(msg))
    }
    //if status code is 200, delcare struct of pointer to items
    var items []*Item
    //use JSON decoder to decode response body in item declaration
    if err := json.NewDecoder(resp.Body).Decode(&items); err != nil {
        return nil, fmt.Errorf("store: can't parse this items response: %v", err)
    }
    return items, nil;
}

type Item struct {

    Word string
    Score int
}

func (it Item) String() string {
    //%q- some sort of primitive that allows you to add the vars in double quotes
    return fmt.Sprintf("Item{Word: %q; Score: %d}", it.Word, it.Score)
}