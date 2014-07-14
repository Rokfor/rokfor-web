**Templates**

Templates connect the HTML and CSS world to the Rokfor Database. Each time you visit a page, the functions within the template are substituted by their return values in the view class.

You can store templates by chapter, issue, book or template name. They have to reside in the subfolder ./chapter, ./issue, ./template.

**Required Templates**

- default.phtml
- sys/404.phtml

*Default*

If no specific template can be found, the system uses default.phtml. If no default.phtml is found, an error is thrown.

*Error*

If an error is thrown, the template ./sys/404.phtml is used to put the response in a stiled format.
