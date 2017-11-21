module Path = {
  type t;
  [@bs.module "react-art"] external make : unit => t = "Path";
  [@bs.send.pipe : t] external move : (~x: int, ~y: int) => t = "";
  [@bs.send.pipe : t] external moveTo : (~x: int, ~y: int) => t = "";
  [@bs.send.pipe : t] external line : (~x: int, ~y: int) => t = "";
  [@bs.send.pipe : t] external lineTo : (~x: int, ~y: int) => t = "";
  [@bs.send.pipe : t]
  external curve : (~c1x: int, ~c1y: int, ~c2x: int, ~c2y: int, ~ex: int, ~ey: int) => t =
    "";
  [@bs.send.pipe : t]
  external curveTo : (~c1x: int, ~c1y: int, ~c2x: int, ~c2y: int, ~ex: int, ~ey: int) => t =
    "";
  [@bs.send.pipe : t]
  external jsArc :
    (
      ~x: int,
      ~y: int,
      ~rx: int,
      ~ry: int,
      ~outer: int,
      ~counterClockwise: Js.boolean,
      ~rotation: int
    ) =>
    t =
    "arc";
  let arc = (~x, ~y, ~rx, ~ry, ~outer, ~counterClockwise, ~rotation, path) =>
    jsArc(
      ~x,
      ~y,
      ~rx,
      ~ry,
      ~outer,
      ~counterClockwise=Js.Boolean.to_js_boolean(counterClockwise),
      ~rotation,
      path
    );
  [@bs.send.pipe : t]
  external jsArcTo :
    (
      ~x: int,
      ~y: int,
      ~rx: int,
      ~ry: int,
      ~outer: int,
      ~counterClockwise: Js.boolean,
      ~rotation: int
    ) =>
    t =
    "arcTo";
  let arcTo = (~x, ~y, ~rx, ~ry, ~outer, ~counterClockwise, ~rotation, path) =>
    jsArcTo(
      ~x,
      ~y,
      ~rx,
      ~ry,
      ~outer,
      ~counterClockwise=Js.Boolean.to_js_boolean(counterClockwise),
      ~rotation,
      path
    );
  [@bs.send.pipe : t]
  external counterArc : (~x: int, ~y: int, ~rx: int, ~ry: int, ~outer: int) => t =
    "";
  [@bs.send.pipe : t]
  external counterArcTo : (~x: int, ~y: int, ~rx: int, ~ry: int, ~outer: int) => t =
    "";
  [@bs.send.pipe : t] external close : t = "";
};

module Transform = {
  type t;
  type point = {
    x: int,
    y: int
  };
  type jsPoint = {. "x": int, "y": int};
  let jsPointToReason = (jsPoint: jsPoint) => {x: jsPoint##x, y: jsPoint##y};
  [@bs.module "react-art"] [@bs.new] external make : unit => t = "Transform";
  [@bs.module "react-art"] [@bs.new]
  external makeWithArgs : (~xx: int, ~yx: int, ~xy: int, ~yy: int, ~x: int, ~y: int, unit) => t =
    "Transform";
  [@bs.send.pipe : t]
  external transform : (~xx: int, ~yx: int, ~xy: int, ~yy: int, ~x: int, ~y: int, unit) => t =
    "";
  [@bs.send.pipe : t] external translate : (~x: int, ~y: int) => t = "";
  [@bs.send.pipe : t] external move : (~x: int, ~y: int) => t = "";
  [@bs.send.pipe : t] external moveTo : (~x: int, ~y: int) => t = "";
  [@bs.send.pipe : t] external scale : (~x: int, ~y: int) => t = "";
  [@bs.send.pipe : t] external scaleTo : (~x: int, ~y: int) => t = "";
  [@bs.send.pipe : t] external rotate : (~deg: int, ~x: int, ~y: int) => t = "";
  [@bs.send.pipe : t] external rotateTo : (~deg: int, ~x: int, ~y: int) => t = "";
  [@bs.send.pipe : t] external resizeTo : (~width: int, ~height: int) => t = "";
  [@bs.send.pipe : t] external jsPoint : (~x: int, ~y: int) => jsPoint = "point";
  [@bs.send.pipe : t] external jsInversePoint : (~x: int, ~y: int) => jsPoint = "inversePoint";
  let point = (~x, ~y, t) => jsPoint(~x, ~y, t) |> jsPointToReason;
  let inversePoint = (~x, ~y, t) => jsInversePoint(~x, ~y, t) |> jsPointToReason;
};

module Pattern = {
  type t;
  [@bs.module "react-art"] [@bs.new]
  external make : (~url: string, ~width: int, ~height: int, ~left: int, ~top: int) => t =
    "Pattern";
};

let stopsToJs = (stops) =>
  List.fold_left(
    (dict, (key, value)) => {
      Js.Dict.set(dict, key, value);
      dict
    },
    Js.Dict.empty(),
    stops
  );

module LinearGradient = {
  type t;
  [@bs.module "react-art"] [@bs.new]
  external makeFromArrayStops :
    (~stops: array(string), ~x1: int, ~y1: int, ~x2: int, ~y2: int) => t =
    "LinearGradient";
  [@bs.module "react-art"] [@bs.new]
  external makeFromJsStops :
    (~stops: Js.Dict.t(string), ~x1: int, ~y1: int, ~x2: int, ~y2: int) => t =
    "LinearGradient";
  let make = (~stops, ~x1, ~y1, ~x2, ~y2) =>
    makeFromJsStops(~stops=stopsToJs(stops), ~x1, ~y1, ~x2, ~y2);
};

module RadialGradient = {
  type t;
  [@bs.module "react-art"] [@bs.new]
  external makeFromArrayStops :
    (~stops: array(string), ~fx: int, ~fy: int, ~rx: int, ~ry: int, ~cx: int, ~cy: int) => t =
    "RadialGradient";
  [@bs.module "react-art"] [@bs.new]
  external makeFromJsStops :
    (~stops: Js.Dict.t(string), ~fx: int, ~fy: int, ~rx: int, ~ry: int, ~cx: int, ~cy: int) => t =
    "RadialGradient";
  let make = (~stops, ~fx, ~fy, ~rx, ~ry, ~cx, ~cy) =>
    makeFromJsStops(~stops=stopsToJs(stops), ~fx, ~fy, ~rx, ~ry, ~cx, ~cy);
};

[@bs.module "react-art"] external surface : ReasonReact.reactClass = "Surface";

module Surface = {
  let make =
      (
        ~width: int,
        ~height: int,
        ~className: option(string)=?,
        ~style: option(ReactDOMRe.style)=?,
        ~role: option(string)=?,
        ~title: option(string)=?,
        ~tabIndex: option(int)=?,
        ~draggable=false,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=surface,
      ~props={
        "width": width,
        "height": height,
        "className": Js.Null.from_opt(className),
        "style": Js.Null.from_opt(style),
        "tabIndex": Js.Null.from_opt(tabIndex),
        "role": Js.Null.from_opt(role),
        "title": Js.Null.from_opt(title),
        "draggable": Js.Boolean.to_js_boolean(draggable)
      },
      children
    );
};

type fill =
  | String(string)
  | LinearGradient(LinearGradient.t)
  | RadialGradient(RadialGradient.t)
  | Pattern(Pattern.t);

type jsFill;

external stringToJsFill : string => jsFill = "%identity";

external linearGradientToJsFill : LinearGradient.t => jsFill = "%identity";

external radialGradientToJsFill : RadialGradient.t => jsFill = "%identity";

external patternToJsFill : Pattern.t => jsFill = "%identity";

let fillToJs = (fill) =>
  switch fill {
  | Some(fill) =>
    switch fill {
    | String(v) => Js.Null.return(stringToJsFill(v))
    | LinearGradient(v) => Js.Null.return(linearGradientToJsFill(v))
    | RadialGradient(v) => Js.Null.return(radialGradientToJsFill(v))
    | Pattern(v) => Js.Null.return(patternToJsFill(v))
    }
  | None => Js.Null.empty
  };

[@bs.module "react-art"] external group : ReasonReact.reactClass = "Group";

module Group = {
  let make =
      (
        ~width: option(int)=?,
        ~height: option(int)=?,
        ~scaleX: option(float)=?,
        ~scaleY: option(float)=?,
        ~scale: option(float)=?,
        ~x: option(int)=?,
        ~y: option(int)=?,
        ~originX: option(int)=?,
        ~originY: option(int)=?,
        ~transform: option(Transform.t)=?,
        ~cursor: option(string)=?,
        ~opacity: option(float)=?,
        ~visible=true,
        ~onMouseMove: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseOver: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseOut: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseUp: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseDown: option((DomRe.MouseEvent.t => unit))=?,
        ~onClick: option((DomRe.MouseEvent.t => unit))=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=group,
      ~props={
        "width": Js.Null_undefined.from_opt(width),
        "height": Js.Null_undefined.from_opt(height),
        "scaleX": Js.Null_undefined.from_opt(scaleX),
        "scaleY": Js.Null_undefined.from_opt(scaleY),
        "scale": Js.Null_undefined.from_opt(scale),
        "x": Js.Null_undefined.from_opt(x),
        "y": Js.Null_undefined.from_opt(y),
        "originX": Js.Null_undefined.from_opt(originX),
        "originY": Js.Null_undefined.from_opt(originY),
        "transform": Js.Null_undefined.from_opt(transform),
        "cursor": Js.Null_undefined.from_opt(cursor),
        "opacity": Js.Null_undefined.from_opt(opacity),
        "visible": Js.Boolean.to_js_boolean(visible),
        "onMouseMove": Js.Null_undefined.from_opt(onMouseMove),
        "onMouseOver": Js.Null_undefined.from_opt(onMouseOver),
        "onMouseOut": Js.Null_undefined.from_opt(onMouseOut),
        "onMouseUp": Js.Null_undefined.from_opt(onMouseUp),
        "onMouseDown": Js.Null_undefined.from_opt(onMouseDown),
        "onClick": Js.Null_undefined.from_opt(onClick)
      },
      children
    );
};

[@bs.module "react-art"] external text : ReasonReact.reactClass = "Text";

module Text = {
  let make =
      (
        ~font: option(string)=?,
        ~fontSize: option(int)=?,
        ~fontStyle: option(string)=?,
        ~fontVariant: option(int)=?,
        ~fontWeight: option(string)=?,
        ~fontFamily: option(string)=?,
        ~alignment: option(string)=?,
        ~path: option(Path.t)=?,
        ~fill: option(fill)=?,
        ~stroke: option(string)=?,
        ~strokeWidth: option(int)=?,
        ~strokeCap: option(string)=?,
        ~strokeJoin: option(string)=?,
        ~strokeDash: option(string)=?,
        ~scaleX: option(float)=?,
        ~scaleY: option(float)=?,
        ~scale: option(float)=?,
        ~x: option(int)=?,
        ~y: option(int)=?,
        ~originX: option(int)=?,
        ~originY: option(int)=?,
        ~transform: option(Transform.t)=?,
        ~cursor: option(string)=?,
        ~opacity: option(float)=?,
        ~visible=true,
        ~onMouseMove: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseOver: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseOut: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseUp: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseDown: option((DomRe.MouseEvent.t => unit))=?,
        ~onClick: option((DomRe.MouseEvent.t => unit))=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=text,
      ~props={
        "font": Js.Null.from_opt(font),
        "fontSize": Js.Null.from_opt(fontSize),
        "fontStyle": Js.Null.from_opt(fontStyle),
        "fontVariant": Js.Null.from_opt(fontVariant),
        "fontWeight": Js.Null.from_opt(fontWeight),
        "fontFamily": Js.Null.from_opt(fontFamily),
        "alignment": Js.Null.from_opt(alignment),
        "path": Js.Null.from_opt(path),
        "fill": fillToJs(fill),
        "stroke": Js.Null_undefined.from_opt(stroke),
        "strokeWidth": Js.Null_undefined.from_opt(strokeWidth),
        "strokeCap": Js.Null_undefined.from_opt(strokeCap),
        "strokeJoin": Js.Null_undefined.from_opt(strokeJoin),
        "strokeDash": Js.Null_undefined.from_opt(strokeDash),
        "scaleX": Js.Null_undefined.from_opt(scaleX),
        "scaleY": Js.Null_undefined.from_opt(scaleY),
        "scale": Js.Null_undefined.from_opt(scale),
        "x": Js.Null_undefined.from_opt(x),
        "y": Js.Null_undefined.from_opt(y),
        "originX": Js.Null_undefined.from_opt(originX),
        "originY": Js.Null_undefined.from_opt(originY),
        "transform": Js.Null_undefined.from_opt(transform),
        "cursor": Js.Null_undefined.from_opt(cursor),
        "opacity": Js.Null_undefined.from_opt(opacity),
        "visible": Js.Boolean.to_js_boolean(visible),
        "onMouseMove": Js.Null_undefined.from_opt(onMouseMove),
        "onMouseOver": Js.Null_undefined.from_opt(onMouseOver),
        "onMouseOut": Js.Null_undefined.from_opt(onMouseOut),
        "onMouseUp": Js.Null_undefined.from_opt(onMouseUp),
        "onMouseDown": Js.Null_undefined.from_opt(onMouseDown),
        "onClick": Js.Null_undefined.from_opt(onClick)
      },
      children
    );
};

[@bs.module "react-art"] external shape : ReasonReact.reactClass = "Shape";

module Shape = {
  let make =
      (
        ~d: Path.t,
        ~width: option(int)=?,
        ~height: option(int)=?,
        ~fill: option(fill)=?,
        ~stroke: option(string)=?,
        ~strokeWidth: option(int)=?,
        ~strokeCap: option(string)=?,
        ~strokeJoin: option(string)=?,
        ~strokeDash: option(string)=?,
        ~scaleX: option(float)=?,
        ~scaleY: option(float)=?,
        ~scale: option(float)=?,
        ~x: option(int)=?,
        ~y: option(int)=?,
        ~originX: option(int)=?,
        ~originY: option(int)=?,
        ~transform: option(Transform.t)=?,
        ~cursor: option(string)=?,
        ~opacity: option(float)=?,
        ~visible=true,
        ~onMouseMove: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseOver: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseOut: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseUp: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseDown: option((DomRe.MouseEvent.t => unit))=?,
        ~onClick: option((DomRe.MouseEvent.t => unit))=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=shape,
      ~props={
        "d": d,
        "width": Js.Null_undefined.from_opt(width),
        "height": Js.Null_undefined.from_opt(height),
        "fill": fillToJs(fill),
        "stroke": Js.Null_undefined.from_opt(stroke),
        "strokeWidth": Js.Null_undefined.from_opt(strokeWidth),
        "strokeCap": Js.Null_undefined.from_opt(strokeCap),
        "strokeJoin": Js.Null_undefined.from_opt(strokeJoin),
        "strokeDash": Js.Null_undefined.from_opt(strokeDash),
        "scaleX": Js.Null_undefined.from_opt(scaleX),
        "scaleY": Js.Null_undefined.from_opt(scaleY),
        "scale": Js.Null_undefined.from_opt(scale),
        "x": Js.Null_undefined.from_opt(x),
        "y": Js.Null_undefined.from_opt(y),
        "originX": Js.Null_undefined.from_opt(originX),
        "originY": Js.Null_undefined.from_opt(originY),
        "transform": Js.Null_undefined.from_opt(transform),
        "cursor": Js.Null_undefined.from_opt(cursor),
        "opacity": Js.Null_undefined.from_opt(opacity),
        "visible": Js.Boolean.to_js_boolean(visible),
        "onMouseMove": Js.Null_undefined.from_opt(onMouseMove),
        "onMouseOver": Js.Null_undefined.from_opt(onMouseOver),
        "onMouseOut": Js.Null_undefined.from_opt(onMouseOut),
        "onMouseUp": Js.Null_undefined.from_opt(onMouseUp),
        "onMouseDown": Js.Null_undefined.from_opt(onMouseDown),
        "onClick": Js.Null_undefined.from_opt(onClick)
      },
      children
    );
};

[@bs.module] external rectangle : ReasonReact.reactClass = "react-art/lib/Rectangle.art";

module Rectangle = {
  let make =
      (
        ~width: option(int)=?,
        ~height: option(int)=?,
        ~radius: option(int)=?,
        ~radiusTopLeft: option(int)=?,
        ~radiusTopRight: option(int)=?,
        ~radiusBottomRight: option(int)=?,
        ~radiusBottomLeft: option(int)=?,
        ~fill: option(fill)=?,
        ~stroke: option(string)=?,
        ~strokeWidth: option(int)=?,
        ~strokeCap: option(string)=?,
        ~strokeJoin: option(string)=?,
        ~strokeDash: option(string)=?,
        ~scaleX: option(float)=?,
        ~scaleY: option(float)=?,
        ~scale: option(float)=?,
        ~x: option(int)=?,
        ~y: option(int)=?,
        ~originX: option(int)=?,
        ~originY: option(int)=?,
        ~transform: option(Transform.t)=?,
        ~cursor: option(string)=?,
        ~opacity: option(float)=?,
        ~visible=true,
        ~onMouseMove: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseOver: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseOut: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseUp: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseDown: option((DomRe.MouseEvent.t => unit))=?,
        ~onClick: option((DomRe.MouseEvent.t => unit))=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=rectangle,
      ~props={
        "width": Js.Null_undefined.from_opt(width),
        "height": Js.Null_undefined.from_opt(height),
        "radius": Js.Null_undefined.from_opt(radius),
        "radiusTopLeft": Js.Null_undefined.from_opt(radiusTopLeft),
        "radiusTopRight": Js.Null_undefined.from_opt(radiusTopRight),
        "radiusBottomRight": Js.Null_undefined.from_opt(radiusBottomRight),
        "radiusBottomLeft": Js.Null_undefined.from_opt(radiusBottomLeft),
        "fill": fillToJs(fill),
        "stroke": Js.Null_undefined.from_opt(stroke),
        "strokeWidth": Js.Null_undefined.from_opt(strokeWidth),
        "strokeCap": Js.Null_undefined.from_opt(strokeCap),
        "strokeJoin": Js.Null_undefined.from_opt(strokeJoin),
        "strokeDash": Js.Null_undefined.from_opt(strokeDash),
        "scaleX": Js.Null_undefined.from_opt(scaleX),
        "scaleY": Js.Null_undefined.from_opt(scaleY),
        "scale": Js.Null_undefined.from_opt(scale),
        "x": Js.Null_undefined.from_opt(x),
        "y": Js.Null_undefined.from_opt(y),
        "originX": Js.Null_undefined.from_opt(originX),
        "originY": Js.Null_undefined.from_opt(originY),
        "transform": Js.Null_undefined.from_opt(transform),
        "cursor": Js.Null_undefined.from_opt(cursor),
        "opacity": Js.Null_undefined.from_opt(opacity),
        "visible": Js.Boolean.to_js_boolean(visible),
        "onMouseMove": Js.Null_undefined.from_opt(onMouseMove),
        "onMouseOver": Js.Null_undefined.from_opt(onMouseOver),
        "onMouseOut": Js.Null_undefined.from_opt(onMouseOut),
        "onMouseUp": Js.Null_undefined.from_opt(onMouseUp),
        "onMouseDown": Js.Null_undefined.from_opt(onMouseDown),
        "onClick": Js.Null_undefined.from_opt(onClick)
      },
      children
    );
};

[@bs.module] external circle : ReasonReact.reactClass = "react-art/lib/Circle.art";

module Circle = {
  let make =
      (
        ~radius: int,
        ~fill: option(fill)=?,
        ~stroke: option(string)=?,
        ~strokeWidth: option(int)=?,
        ~strokeCap: option(string)=?,
        ~strokeJoin: option(string)=?,
        ~strokeDash: option(string)=?,
        ~scaleX: option(float)=?,
        ~scaleY: option(float)=?,
        ~scale: option(float)=?,
        ~x: option(int)=?,
        ~y: option(int)=?,
        ~originX: option(int)=?,
        ~originY: option(int)=?,
        ~transform: option(Transform.t)=?,
        ~cursor: option(string)=?,
        ~opacity: option(float)=?,
        ~visible=true,
        ~onMouseMove: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseOver: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseOut: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseUp: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseDown: option((DomRe.MouseEvent.t => unit))=?,
        ~onClick: option((DomRe.MouseEvent.t => unit))=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=circle,
      ~props={
        "radius": radius,
        "fill": fillToJs(fill),
        "stroke": Js.Null_undefined.from_opt(stroke),
        "strokeWidth": Js.Null_undefined.from_opt(strokeWidth),
        "strokeCap": Js.Null_undefined.from_opt(strokeCap),
        "strokeJoin": Js.Null_undefined.from_opt(strokeJoin),
        "strokeDash": Js.Null_undefined.from_opt(strokeDash),
        "scaleX": Js.Null_undefined.from_opt(scaleX),
        "scaleY": Js.Null_undefined.from_opt(scaleY),
        "scale": Js.Null_undefined.from_opt(scale),
        "x": Js.Null_undefined.from_opt(x),
        "y": Js.Null_undefined.from_opt(y),
        "originX": Js.Null_undefined.from_opt(originX),
        "originY": Js.Null_undefined.from_opt(originY),
        "transform": Js.Null_undefined.from_opt(transform),
        "cursor": Js.Null_undefined.from_opt(cursor),
        "opacity": Js.Null_undefined.from_opt(opacity),
        "visible": Js.Boolean.to_js_boolean(visible),
        "onMouseMove": Js.Null_undefined.from_opt(onMouseMove),
        "onMouseOver": Js.Null_undefined.from_opt(onMouseOver),
        "onMouseOut": Js.Null_undefined.from_opt(onMouseOut),
        "onMouseUp": Js.Null_undefined.from_opt(onMouseUp),
        "onMouseDown": Js.Null_undefined.from_opt(onMouseDown),
        "onClick": Js.Null_undefined.from_opt(onClick)
      },
      children
    );
};

[@bs.module] external wedge : ReasonReact.reactClass = "react-art/lib/Wedge.art";

module Wedge = {
  let make =
      (
        ~outerRadius: int,
        ~startAngle: int,
        ~endAngle: int,
        ~innerRadius: option(int)=?,
        ~fill: option(fill)=?,
        ~stroke: option(string)=?,
        ~strokeWidth: option(int)=?,
        ~strokeCap: option(string)=?,
        ~strokeJoin: option(string)=?,
        ~strokeDash: option(string)=?,
        ~scaleX: option(float)=?,
        ~scaleY: option(float)=?,
        ~scale: option(float)=?,
        ~x: option(int)=?,
        ~y: option(int)=?,
        ~originX: option(int)=?,
        ~originY: option(int)=?,
        ~transform: option(Transform.t)=?,
        ~cursor: option(string)=?,
        ~opacity: option(float)=?,
        ~visible=true,
        ~onMouseMove: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseOver: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseOut: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseUp: option((DomRe.MouseEvent.t => unit))=?,
        ~onMouseDown: option((DomRe.MouseEvent.t => unit))=?,
        ~onClick: option((DomRe.MouseEvent.t => unit))=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=wedge,
      ~props={
        "outerRadius": outerRadius,
        "startAngle": startAngle,
        "endAngle": endAngle,
        "innerRadius": Js.Null_undefined.from_opt(innerRadius),
        "fill": fillToJs(fill),
        "stroke": Js.Null_undefined.from_opt(stroke),
        "strokeWidth": Js.Null_undefined.from_opt(strokeWidth),
        "strokeCap": Js.Null_undefined.from_opt(strokeCap),
        "strokeJoin": Js.Null_undefined.from_opt(strokeJoin),
        "strokeDash": Js.Null_undefined.from_opt(strokeDash),
        "scaleX": Js.Null_undefined.from_opt(scaleX),
        "scaleY": Js.Null_undefined.from_opt(scaleY),
        "scale": Js.Null_undefined.from_opt(scale),
        "x": Js.Null_undefined.from_opt(x),
        "y": Js.Null_undefined.from_opt(y),
        "originX": Js.Null_undefined.from_opt(originX),
        "originY": Js.Null_undefined.from_opt(originY),
        "transform": Js.Null_undefined.from_opt(transform),
        "cursor": Js.Null_undefined.from_opt(cursor),
        "opacity": Js.Null_undefined.from_opt(opacity),
        "visible": Js.Boolean.to_js_boolean(visible),
        "onMouseMove": Js.Null_undefined.from_opt(onMouseMove),
        "onMouseOver": Js.Null_undefined.from_opt(onMouseOver),
        "onMouseOut": Js.Null_undefined.from_opt(onMouseOut),
        "onMouseUp": Js.Null_undefined.from_opt(onMouseUp),
        "onMouseDown": Js.Null_undefined.from_opt(onMouseDown),
        "onClick": Js.Null_undefined.from_opt(onClick)
      },
      children
    );
};
