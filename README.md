#rokfor-web

A simple reference implementation of a Rokfor CMS web application.

#Installation

* Prerequisites: A running rokfor installation. Check it out here: <a href="/Rokfor/rokfor-cms">Rokfor-cms</a>
* Clone the repository in the document root
* Make sure, that the path to the Rokfor Configuration exists (rf_config-v2.inc in index.php)
* If you don't change anything, the default paths should work.

#How-To

##Parameters

This repository is a simple template engine. It accepts four GET parameters. In the constructor of controller.class.inc you see:

```
$this->_checkBook($_GET['book']);
$this->_checkIssue($_GET['issue']);
$this->_checkChapter($_GET['chapter']);		
$this->_checkElement($_GET['element']);	
```

If these parameters are omitted, the first available will be set as default.
You can send these parameters when creating a menufunction, or pretty print them with an .htaccess file

```
RewriteRule ^(.*)$ 					/index.php?book=$1 [L]
RewriteRule ^(.*)/(.*)$ 			/index.php?book=$1&issue=$2 [L]
RewriteRule ^(.*)/(.*)/(.*)$ 		/index.php?book=$1&issue=$2&chapter=$3 [L]
RewriteRule ^(.*)/(.*)/(.*)/(.*)$ 	/index.php?book=$1&issue=$2&chapter=$3&element=$4 [L]
```

##Templates


Templates reside in the templates folder. They are html, and you're totally free in designing whatever you want. The little magic is here:
Whenever you write a snippet like this, make sure, that the function $dump_content in this example also exists in the view.class.inc file. 
In the end, make sure, that your template function returns its result as a string. The string will be inserted in the template to make it complete.

```
<?=$dump_content?>
```

You can include a template within a template:

```
<?include('sys/header.phtml')?>
```

Like this, you can set the same footer for every page in one template.

###Data Structures

When you design a function for a template, there are two main data structures holding the necessary data.

```
$this->tree
$this->data
```

$this->tree holds the available books, the issues, the chapters and the elements of the current chapter. You can easily create a menu with it.
$this->data holds the content of the loaded element. You can create a page with it.

If you need to know which book, issue, chapter or element is currently active, it's all stored in these structures. You can use these to highlight the selected section in the menu, for example.

```
$this->book
$this->issue
$this->chapter
$this->element
```

###Loading other than current data


If you need other data than the current, for example in your footer, you can overload the active element data with an own id:

```
$localdata = $this->_loadData($_element);	// Load the content of element with id $_element
$text = $localdata['Textfield'];			// $text holds now the content of the loaded data
$current = $this->data['Textfield'];		// $current holds the content of the default data

```

###Javascript


If you need Java Script Code which should be executed, there's the helper function

```
$this->addDomready($_code) 
```

The code will be added to a onReady Function at the end of the page. It's wrapped in a mootools-flavoured domready function, but you can change the code in the controller.class.inc file at ease:

``` 
	function dump($echo = true) 
	{
		...
			<script type="text/javascript" charset="utf-8">
			window.addEvent(\'domready\', function() {
				'.join("\n",$this->domready).'
				});
			</script>
			');
		...
``` 

If you prefer jquery, you can change the code to:

``` 
	function dump($echo = true) 
	{
		...
			<script type="text/javascript" charset="utf-8">
			$( document ).ready(function() {
				'.join("\n",$this->domready).'
				});
			</script>
			');
		...
``` 

###Example Function


Here's an example for a textfield:

``` 
function texfield() 
{
	$html = $this->data['Textfield'];				// Get the text value of the field "Textfield"
	return ('<p class="content">'.$html.'</p>');	// Wrap it in a tag and return it.
}
```