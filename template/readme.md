**Templates**

Templates connect the HTML and CSS world to the Rokfor Database. Each time you visit a page, the functions within the template are substituted by their return values in the view class.

You can store templates by chapter, issue, book or template name. They have to reside in the subfolder ./chapter, ./issue, ./template.

**Experimental: jade Templates**

If you load the view class with jade enabled, templates need the extension .jade. They will be preprocessed by the php jade compiler ```http://github.com/everzet/jade.php``` and then populated with the data and functions provided within the view class.

**Required Templates**

- default.phtml
- sys/404.phtml

*Default*

If no specific template can be found, the system uses default.phtml. If no default.phtml is found, an error is thrown.

*Error*

If an error is thrown, the template ./sys/404.phtml is used to put the response in a stiled format.

**Relative Includes**

Sometimes, it makes totally sense to include a template within an other template. Mostly used for headers and footers. This can be easily done with include statements. For example:

```
<?include('sys/header.phtml')?>
```

Paths to included files are _always relative_. They start in the configured template directory. The example above will always include [Template_Directory]/sys/header.phtml, no matter where your template is stored. 
