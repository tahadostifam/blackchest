namespace Dtos;

public record class ArticleDto(
    int Id,
    string Title,
    string Slug,
    string Body,
    string Writer,
    DateOnly PublishDate
);

public record class CreateArticleDto(
    string Title,
    string Slug,
    string Body,
    string Writer
);
