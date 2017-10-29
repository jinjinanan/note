



##### app_errorhandler

##### errorhandler
	Registers an error handler that becomes active for this blueprint
        only.  Please be aware that routing does not happen local to a
        blueprint so an error handler for 404 usually is not handled by
        a blueprint unless it is caused inside a view function.  Another
        special case is the 500 internal server error which is always looked
        up from the application.

        Otherwise works as the :meth:`~flask.Flask.errorhandler` decorator
        of the :class:`~flask.Flask` object.
        

| 单词       | 词性   |  词义  |
| --------   | -----:  | :----:  |
|redirect|V|重新调配|
|even if||即使|
|even if outside of the blueprint||即使此视图之外|