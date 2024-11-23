package main

import (
	"log"
	_ "swagger-example/docs"

	"github.com/gin-gonic/gin"
	swaggerfiles "github.com/swaggo/files"
	ginSwagger "github.com/swaggo/gin-swagger"
)

type HttpError struct {
	Code    int    `json:"code"`
	Message string `json:"message"`
}

//	@BasePath	/

// AllPosts godoc
//
//	@Summary		All Posts
//	@Description	gets all posts
//	@Tags			posts
//	@Accept			jsongst
//	@Produce		json
//
// @Failure		400	{object}	HttpError
// @Failure		404	{object}	HttpError
// @Failure		500	{object}	HttpError
// @Router			/posts/ [get]
func AllPostsController(ctx *gin.Context) {
	log.Println(ctx.Params)

	ctx.SecureJSON(500, &HttpError{
		Code:    500,
		Message: "Failed to run the query",
	})
}

// @title			SwaggerExample
// @version		1.0
// @description	A simple example to show how swagger works.
func main() {
	app := gin.Default()

	app.GET("/swagger/*any", ginSwagger.WrapHandler(swaggerfiles.NewHandler()))
	app.GET("/posts", AllPostsController)

	app.Run(":3000")
}
