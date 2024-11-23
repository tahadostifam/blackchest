package main

import (
	"encoding/json"
	"graphql-samples/cache"
	"graphql-samples/db"
	"graphql-samples/graph"
	"log"
	"net/http"
	"os"

	"github.com/99designs/gqlgen/graphql/handler"
	"github.com/99designs/gqlgen/graphql/handler/extension"
	"github.com/99designs/gqlgen/graphql/playground"
)

const defaultPort = "8080"

func main() {
	port := os.Getenv("PORT")
	if port == "" {
		port = defaultPort
	}

	db := db.New()

	srv := handler.NewDefaultServer(graph.NewExecutableSchema(graph.Config{Resolvers: &graph.Resolver{
		DB: db,
	}}))

	cache := &cache.Cache{}

	srv.Use(extension.AutomaticPersistedQuery{
		Cache: cache,
	})

	http.Handle("/", playground.Handler("GraphQL playground", "/query"))
	http.Handle("/query", srv)

	http.HandleFunc("/hash_table", func(w http.ResponseWriter, r *http.Request) {
		hashTableJSON, err := json.Marshal(cache.HashTable)
		if err != nil {
			w.Write([]byte("unable to marshal hashTable into json"))
			return
		}

		w.Write(hashTableJSON)
	})

	log.Printf("connect to http://localhost:%s/ for GraphQL playground", port)
	log.Fatal(http.ListenAndServe(":"+port, nil))
}
