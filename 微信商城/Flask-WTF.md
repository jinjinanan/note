

## 使用
### CSRF 保护
#### 关闭 CSRF 保护
关闭单个表单
`form = Form(csrf_enabled=False)`
关闭全局表单
`WTF_CSRF_ENABLED = False`
#### 设置密令
`WTF_CSRF_SECRET_KEY = 'a random string'`
#### 表单 CSRF 保护
在表单中加入 `{{ form.csrf_token }}`
#### 非表单 CSRF 保护
???

## 源码
### Field
```
class Field(object):
	"""
    Field base class
    """
```
初始化参数
```
def __init__(self, label=None, validators=None, filters=tuple(),
                 description='', id=None, default=None, widget=None,
                 render_kw=None, _form=None, _name=None, _prefix='',
                 _translations=None, _meta=None):
    """
        Construct a new field.

        :param label:
            The label of the field.
        :param validators:
            A sequence of validators to call when `validate` is called.
        :param filters:
            A sequence of filters which are run on input data by `process`.
        :param description:
            A description for the field, typically used for help text.
        :param id:
            An id to use for the field. A reasonable default is set by the form,
            and you shouldn't need to set this manually.
        :param default:
            The default value to assign to the field, if no form or object
            input is provided. May be a callable.
        :param widget:
            If provided, overrides the widget used to render the field.
        :param dict render_kw:
            If provided, a dictionary which provides default keywords that
            will be given to the widget at render time.
        :param _form:
            The form holding this field. It is passed by the form itself during
            construction. You should never pass this value yourself.
        :param _name:
            The name of this field, passed by the enclosing form during its
            construction. You should never pass this value yourself.
        :param _prefix:
            The prefix to prepend to the form name of this field, passed by
            the enclosing form during construction.
        :param _translations:
            A translations object providing message translations. Usually
            passed by the enclosing form during construction. See
            :doc:`I18n docs <i18n>` for information on message translations.
        :param _meta:
            If provided, this is the 'meta' instance from the form. You usually
            don't pass this yourself.

        If `_form` and `_name` isn't provided, an :class:`UnboundField` will be
        returned instead. Call its :func:`bind` method with a form instance and
        a name to construct the field.
    """      
```

渲染HTML方法
```
	    def __call__(self, **kwargs):
        """
        Render this field as HTML, using keyword args as additional attributes.

        This delegates rendering to
        :meth:`meta.render_field <wtforms.meta.DefaultMeta.render_field>`
        whose default behavior is to call the field's widget, passing any
        keyword arguments from this call along to the widget.

        In all of the WTForms HTML widgets, keyword arguments are turned to
        HTML attributes, though in theory a widget is free to do anything it
        wants with the supplied keyword arguments, and widgets don't have to
        even do anything related to HTML.
        """
        return self.meta.render_field(self, kwargs)  
```



| 单词       | 词性   |  词义  |
| --------   | -----:  | :----:  |
|**Integration** with WTForms.|||
|**Secure** Form with CSRF token||||
| Can **render** a file-upload field. |||
|A sequence of **validators** to call when `validate` is called.|||
|validate|TV|使...生效|
|widgets|N|小部件|
| a string containing only whitespace **characters is
    considered false**||视为假|
|Furthermore|adv|而且|