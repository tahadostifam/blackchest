using Dtos;

var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

List<ArticleDto> articles = [
    new (
        1,
        "Hello World",
        "hello-world",
        "My article body",
        "Taha",
        new DateOnly()
    ),
    new (
        2,
        "Hello World 2",
        "hello-world-2",
        "My article body 2",
        "Taha",
        new DateOnly()
    ),
    new (
        3,
        "Hello World 3",
        "hello-world-3",
        "My article body 3",
        "Taha",
        new DateOnly()
    )
];

const string GetArticleEndpoint = "GetArticle";

app.MapGet("/", () =>
{
    return articles;
});

app.MapGet("/{id}", (int id) =>
{
    ArticleDto? article = articles.Find(article => article.Id == id);
    return article is null ? Results.NotFound() : Results.Ok(article);
}).WithName(GetArticleEndpoint);

app.MapPost("/", (CreateArticleDto dto) =>
{
    ArticleDto newArticle = new(
     articles.Count + 1,
     dto.Title,
     dto.Slug,
     dto.Body,
     dto.Writer,
     new DateOnly()
    );

    articles.Add(newArticle);

    return Results.CreatedAtRoute(GetArticleEndpoint, new { id = newArticle }, newArticle);
});

app.Run();
