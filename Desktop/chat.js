function Core()
{
    function initialize()
    {
        alert(rhChat);
    }

    function initTemplates()
    {

    }

    Core.prototype.useTemplate = function(template_name, vars)
    {
        template = $('.templates #' + template_name).html();
        for(var field in vars)
        {
            var re = new RegExp('{{' + field + '}}', 'g');
            template = template.replace(re, vars[field]);
        }
        return template;
    }

    Core.prototype.getBlock = function(source, sender, time)
    {
        var block = $('#chat .msgBlock:last');
        console.log(source);
        if (block.length>0 && block.hasClass('from'+source))
        {
            console.log('found');
            return block;
        }
        template = this.useTemplate('message_block_template', {source:source, sender: sender});
        $('#chat').append(template);
        return $('#chat .msgBlock:last');
    }

    Core.prototype.addMessage = function(source, sender, message_id, time, text)
    {
        block = this.getBlock(source, sender, time)
        template = this.useTemplate('message_template', {message_id:message_id, time:time, message:text});
        block.append(template);
    }

    Core.prototype.test = function(){
        for(var i=0;i<1000;i++)
        {
            var source = 'Visitor';
            var sender = '#1135031'
            var message = 'Привет! Я хочу купить у вас автомобиль <a href="http://redhelper.ru#123" target="_blank">БТР</a>. Можно заказать драйв-тест? И в какие расцветки доступны?';
             if (Math.random()<0.5)
             {
                 source = 'Operator';
                 sender = 'Вася Пупкин';
                 message = 'К сожалению, все БТР уже закончились. Можем предложить вам отличный седан Т-34! Отличная проходимость! Не требовательный к топливу. Может парковаться не зависимо от занятости парковочного места';
             }
            core.addMessage(source, sender, '32312312312312', '12:09', message);
        }
    }
    //$(Core.prototype.test);
}

window.core = new Core();
$(window.core.initialize);