local function attr_value(text, name)
  return text:match(name .. '="([^"]*)"') or ""
end

local function escape_html(text)
  text = text:gsub("&", "&amp;")
  text = text:gsub("<", "&lt;")
  text = text:gsub(">", "&gt;")
  text = text:gsub('"', "&quot;")
  return text
end

function RawBlock(block)
  if block.format ~= "html" then
    return nil
  end

  local class = attr_value(block.text, "class")
  if class == "convention" then
    local id = escape_html(attr_value(block.text, "id"))
    local title = escape_html(attr_value(block.text, "data%-title"))
    local header = '<div class="convention-title"><span class="convention-id">' ..
      id .. '</span> ' .. title .. '</div>'

    return { block, pandoc.RawBlock("html", header) }
  end

  if class == "draft" then
    return { block, pandoc.RawBlock("html", '<div class="draft-title">PARAGRAPH:</div>') }
  end

  if class == "note" then
    local title = escape_html(attr_value(block.text, "data%-title"))
    if title == "" then
      title = "Note"
    end
    return { block, pandoc.RawBlock("html", '<div class="note-title">' .. title .. ':</div>') }
  end

  return nil
end
