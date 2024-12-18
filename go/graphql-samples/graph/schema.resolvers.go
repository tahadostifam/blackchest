package graph

// This file will be automatically regenerated based on the schema, any resolver implementations
// will be copied through when generating and any unknown code will be moved to the end.
// Code generated by github.com/99designs/gqlgen version v0.17.56

import (
	"context"
	"errors"
	"graphql-samples/db"
	"graphql-samples/graph/model"
	"log"

	"github.com/99designs/gqlgen/graphql"
)

// CreateTodo is the resolver for the createTodo field.
func (r *mutationResolver) CreateTodo(ctx context.Context, input model.NewTodo) (*model.Todo, error) {
	var creatorUser *db.User

	if r.DB.Model(&db.User{}).Find(&creatorUser, input.UserID).Error != nil {
		return nil, errors.New("user with the given user id does not exist")
	}

	todo := &db.Todo{
		Text:   input.Text,
		User:   *creatorUser,
		UserID: creatorUser.ID,
		Done:   false,
	}

	tx := r.DB.Model(&db.Todo{}).Create(&todo)
	if tx.Error != nil {
		return nil, errors.New("unable to create the todo")
	}

	return &model.Todo{
		ID:   int(todo.ID),
		Text: todo.Text,
		Done: todo.Done,
		User: &model.User{
			ID:   int(creatorUser.ID),
			Name: creatorUser.Name,
		},
	}, nil
}

// CreateUser is the resolver for the createUser field.
func (r *mutationResolver) CreateUser(ctx context.Context, input model.NewUser) (*model.User, error) {
	user := &db.User{
		Name: input.Name,
	}

	tx := r.DB.Create(&user)
	if tx.Error != nil {
		log.Println(tx.Error)
		return nil, errors.New("unable to create the user")
	}

	return &model.User{
		ID:   int(user.ID),
		Name: user.Name,
	}, nil
}

// DoSomeThing is the resolver for the doSomeThing field.
func (r *mutationResolver) DoSomeThing(ctx context.Context, input model.NewUser) (*model.User, error) {
	graphql.AddErrorf(ctx, "This a custom error that has written by Taha from SchemaResolver.")
	return nil, nil
}

// Todos is the resolver for the todos field.
func (r *queryResolver) Todos(ctx context.Context) ([]*model.Todo, error) {
	var todos []*db.Todo

	err := r.DB.Model(&db.Todo{}).Find(&todos).Error
	if err != nil {
		return nil, err
	}

	var modelTodos []*model.Todo

	for _, v := range todos {
		modelTodos = append(modelTodos, &model.Todo{
			ID:   int(v.ID),
			Text: v.Text,
			Done: v.Done,
			User: &model.User{
				ID:   int(v.User.ID),
				Name: v.User.Name,
			},
		})
	}

	return modelTodos, nil
}

// Mutation returns MutationResolver implementation.
func (r *Resolver) Mutation() MutationResolver { return &mutationResolver{r} }

// Query returns QueryResolver implementation.
func (r *Resolver) Query() QueryResolver { return &queryResolver{r} }

type mutationResolver struct{ *Resolver }
type queryResolver struct{ *Resolver }
