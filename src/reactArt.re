module Path = {
  type t;
  [@bs.module "react-art"] external make : unit => t = "Path";
  [@bs.send.pipe: t] external move : (~x: int, ~y: int) => t = "";
  [@bs.send.pipe: t] external moveTo : (~x: int, ~y: int) => t = "";
  [@bs.send.pipe: t] external line : (~x: int, ~y: int) => t = "";
  [@bs.send.pipe: t] external lineTo : (~x: int, ~y: int) => t = "";
  [@bs.send.pipe: t]
  external curve :
    (~c1x: int, ~c1y: int, ~c2x: int, ~c2y: int, ~ex: int, ~ey: int) => t =
    "";
  [@bs.send.pipe: t]
  external curveTo :
    (~c1x: int, ~c1y: int, ~c2x: int, ~c2y: int, ~ex: int, ~ey: int) => t =
    "";
  [@bs.send.pipe: t]
  external jsArc :
    (
      ~x: int,
      ~y: int,
      ~rx: int,
      ~ry: int,
      ~outer: int,
      ~counterClockwise: bool,
      ~rotation: int
    ) =>
    t =
    "arc";
  let arc = (~x, ~y, ~rx, ~ry, ~outer, ~counterClockwise, ~rotation, path) =>
    jsArc(~x, ~y, ~rx, ~ry, ~outer, ~counterClockwise, ~rotation, path);
  [@bs.send.pipe: t]
  external jsArcTo :
    (
      ~x: int,
      ~y: int,
      ~rx: int,
      ~ry: int,
      ~outer: int,
      ~counterClockwise: bool,
      ~rotation: int
    ) =>
    t =
    "arcTo";
  let arcTo = (~x, ~y, ~rx, ~ry, ~outer, ~counterClockwise, ~rotation, path) =>
    jsArcTo(~x, ~y, ~rx, ~ry, ~outer, ~counterClockwise, ~rotation, path);
  [@bs.send.pipe: t]
  external counterArc :
    (~x: int, ~y: int, ~rx: int, ~ry: int, ~outer: int) => t =
    "";
  [@bs.send.pipe: t]
  external counterArcTo :
    (~x: int, ~y: int, ~rx: int, ~ry: int, ~outer: int) => t =
    "";
  [@bs.send.pipe: t] external close : t = "";
};

module Transform = {
  type t;
  type point = {
    x: int,
    y: int,
  };
  type jsPoint = {
    .
    "x": int,
    "y": int,
  };
  let jsPointToReason = (jsPoint: jsPoint) => {x: jsPoint##x, y: jsPoint##y};
  [@bs.module "react-art"] [@bs.new] external make : unit => t = "Transform";
  [@bs.module "react-art"] [@bs.new]
  external makeWithArgs :
    (~xx: int, ~yx: int, ~xy: int, ~yy: int, ~x: int, ~y: int, unit) => t =
    "Transform";
  [@bs.send.pipe: t]
  external transform :
    (~xx: int, ~yx: int, ~xy: int, ~yy: int, ~x: int, ~y: int, unit) => t =
    "";
  [@bs.send.pipe: t] external translate : (~x: int, ~y: int) => t = "";
  [@bs.send.pipe: t] external move : (~x: int, ~y: int) => t = "";
  [@bs.send.pipe: t] external moveTo : (~x: int, ~y: int) => t = "";
  [@bs.send.pipe: t] external scale : (~x: int, ~y: int) => t = "";
  [@bs.send.pipe: t] external scaleTo : (~x: int, ~y: int) => t = "";
  [@bs.send.pipe: t] external rotate : (~deg: int, ~x: int, ~y: int) => t = "";
  [@bs.send.pipe: t]
  external rotateTo : (~deg: int, ~x: int, ~y: int) => t = "";
  [@bs.send.pipe: t] external resizeTo : (~width: int, ~height: int) => t = "";
  [@bs.send.pipe: t]
  external jsPoint : (~x: int, ~y: int) => jsPoint = "point";
  [@bs.send.pipe: t]
  external jsInversePoint : (~x: int, ~y: int) => jsPoint = "inversePoint";
  let point = (~x, ~y, t) => jsPoint(~x, ~y, t) |> jsPointToReason;
  let inversePoint = (~x, ~y, t) =>
    jsInversePoint(~x, ~y, t) |> jsPointToReason;
};

module Pattern = {
  type t;
  [@bs.module "react-art"] [@bs.new]
  external make :
    (~url: string, ~width: int, ~height: int, ~left: int, ~top: int) => t =
    "Pattern";
};

let stopsToJs = stops =>
  List.fold_left(
    (dict, (key, value)) => {
      Js.Dict.set(dict, key, value);
      dict;
    },
    Js.Dict.empty(),
    stops,
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
    (
      ~stops: array(string),
      ~fx: int,
      ~fy: int,
      ~rx: int,
      ~ry: int,
      ~cx: int,
      ~cy: int
    ) =>
    t =
    "RadialGradient";
  [@bs.module "react-art"] [@bs.new]
  external makeFromJsStops :
    (
      ~stops: Js.Dict.t(string),
      ~fx: int,
      ~fy: int,
      ~rx: int,
      ~ry: int,
      ~cx: int,
      ~cy: int
    ) =>
    t =
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
        children,
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=surface,
      ~props={
        "width": width,
        "height": height,
        "className": Js.Null.fromOption(className),
        "style": Js.Null.fromOption(style),
        "tabIndex": Js.Null.fromOption(tabIndex),
        "role": Js.Null.fromOption(role),
        "title": Js.Null.fromOption(title),
        "draggable": draggable,
      },
      children,
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

let fillToJs = fill =>
  switch (fill) {
  | Some(fill) =>
    switch (fill) {
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
        ~onMouseMove: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseOver: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseOut: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseUp: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseDown: option(DomRe.MouseEvent.t => unit)=?,
        ~onClick: option(DomRe.MouseEvent.t => unit)=?,
        children,
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=group,
      ~props={
        "width": Js.Nullable.fromOption(width),
        "height": Js.Nullable.fromOption(height),
        "scaleX": Js.Nullable.fromOption(scaleX),
        "scaleY": Js.Nullable.fromOption(scaleY),
        "scale": Js.Nullable.fromOption(scale),
        "x": Js.Nullable.fromOption(x),
        "y": Js.Nullable.fromOption(y),
        "originX": Js.Nullable.fromOption(originX),
        "originY": Js.Nullable.fromOption(originY),
        "transform": Js.Nullable.fromOption(transform),
        "cursor": Js.Nullable.fromOption(cursor),
        "opacity": Js.Nullable.fromOption(opacity),
        "visible": visible,
        "onMouseMove": Js.Nullable.fromOption(onMouseMove),
        "onMouseOver": Js.Nullable.fromOption(onMouseOver),
        "onMouseOut": Js.Nullable.fromOption(onMouseOut),
        "onMouseUp": Js.Nullable.fromOption(onMouseUp),
        "onMouseDown": Js.Nullable.fromOption(onMouseDown),
        "onClick": Js.Nullable.fromOption(onClick),
      },
      children,
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
        ~onMouseMove: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseOver: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseOut: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseUp: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseDown: option(DomRe.MouseEvent.t => unit)=?,
        ~onClick: option(DomRe.MouseEvent.t => unit)=?,
        children,
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=text,
      ~props={
        "font": Js.Null.fromOption(font),
        "fontSize": Js.Null.fromOption(fontSize),
        "fontStyle": Js.Null.fromOption(fontStyle),
        "fontVariant": Js.Null.fromOption(fontVariant),
        "fontWeight": Js.Null.fromOption(fontWeight),
        "fontFamily": Js.Null.fromOption(fontFamily),
        "alignment": Js.Null.fromOption(alignment),
        "path": Js.Null.fromOption(path),
        "fill": fillToJs(fill),
        "stroke": Js.Nullable.fromOption(stroke),
        "strokeWidth": Js.Nullable.fromOption(strokeWidth),
        "strokeCap": Js.Nullable.fromOption(strokeCap),
        "strokeJoin": Js.Nullable.fromOption(strokeJoin),
        "strokeDash": Js.Nullable.fromOption(strokeDash),
        "scaleX": Js.Nullable.fromOption(scaleX),
        "scaleY": Js.Nullable.fromOption(scaleY),
        "scale": Js.Nullable.fromOption(scale),
        "x": Js.Nullable.fromOption(x),
        "y": Js.Nullable.fromOption(y),
        "originX": Js.Nullable.fromOption(originX),
        "originY": Js.Nullable.fromOption(originY),
        "transform": Js.Nullable.fromOption(transform),
        "cursor": Js.Nullable.fromOption(cursor),
        "opacity": Js.Nullable.fromOption(opacity),
        "visible": visible,
        "onMouseMove": Js.Nullable.fromOption(onMouseMove),
        "onMouseOver": Js.Nullable.fromOption(onMouseOver),
        "onMouseOut": Js.Nullable.fromOption(onMouseOut),
        "onMouseUp": Js.Nullable.fromOption(onMouseUp),
        "onMouseDown": Js.Nullable.fromOption(onMouseDown),
        "onClick": Js.Nullable.fromOption(onClick),
      },
      children,
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
        ~onMouseMove: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseOver: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseOut: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseUp: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseDown: option(DomRe.MouseEvent.t => unit)=?,
        ~onClick: option(DomRe.MouseEvent.t => unit)=?,
        children,
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=shape,
      ~props={
        "d": d,
        "width": Js.Nullable.fromOption(width),
        "height": Js.Nullable.fromOption(height),
        "fill": fillToJs(fill),
        "stroke": Js.Nullable.fromOption(stroke),
        "strokeWidth": Js.Nullable.fromOption(strokeWidth),
        "strokeCap": Js.Nullable.fromOption(strokeCap),
        "strokeJoin": Js.Nullable.fromOption(strokeJoin),
        "strokeDash": Js.Nullable.fromOption(strokeDash),
        "scaleX": Js.Nullable.fromOption(scaleX),
        "scaleY": Js.Nullable.fromOption(scaleY),
        "scale": Js.Nullable.fromOption(scale),
        "x": Js.Nullable.fromOption(x),
        "y": Js.Nullable.fromOption(y),
        "originX": Js.Nullable.fromOption(originX),
        "originY": Js.Nullable.fromOption(originY),
        "transform": Js.Nullable.fromOption(transform),
        "cursor": Js.Nullable.fromOption(cursor),
        "opacity": Js.Nullable.fromOption(opacity),
        "visible": visible,
        "onMouseMove": Js.Nullable.fromOption(onMouseMove),
        "onMouseOver": Js.Nullable.fromOption(onMouseOver),
        "onMouseOut": Js.Nullable.fromOption(onMouseOut),
        "onMouseUp": Js.Nullable.fromOption(onMouseUp),
        "onMouseDown": Js.Nullable.fromOption(onMouseDown),
        "onClick": Js.Nullable.fromOption(onClick),
      },
      children,
    );
};

[@bs.module]
external rectangle : ReasonReact.reactClass = "react-art/Rectangle";

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
        ~onMouseMove: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseOver: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseOut: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseUp: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseDown: option(DomRe.MouseEvent.t => unit)=?,
        ~onClick: option(DomRe.MouseEvent.t => unit)=?,
        children,
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=rectangle,
      ~props={
        "width": Js.Nullable.fromOption(width),
        "height": Js.Nullable.fromOption(height),
        "radius": Js.Nullable.fromOption(radius),
        "radiusTopLeft": Js.Nullable.fromOption(radiusTopLeft),
        "radiusTopRight": Js.Nullable.fromOption(radiusTopRight),
        "radiusBottomRight": Js.Nullable.fromOption(radiusBottomRight),
        "radiusBottomLeft": Js.Nullable.fromOption(radiusBottomLeft),
        "fill": fillToJs(fill),
        "stroke": Js.Nullable.fromOption(stroke),
        "strokeWidth": Js.Nullable.fromOption(strokeWidth),
        "strokeCap": Js.Nullable.fromOption(strokeCap),
        "strokeJoin": Js.Nullable.fromOption(strokeJoin),
        "strokeDash": Js.Nullable.fromOption(strokeDash),
        "scaleX": Js.Nullable.fromOption(scaleX),
        "scaleY": Js.Nullable.fromOption(scaleY),
        "scale": Js.Nullable.fromOption(scale),
        "x": Js.Nullable.fromOption(x),
        "y": Js.Nullable.fromOption(y),
        "originX": Js.Nullable.fromOption(originX),
        "originY": Js.Nullable.fromOption(originY),
        "transform": Js.Nullable.fromOption(transform),
        "cursor": Js.Nullable.fromOption(cursor),
        "opacity": Js.Nullable.fromOption(opacity),
        "visible": visible,
        "onMouseMove": Js.Nullable.fromOption(onMouseMove),
        "onMouseOver": Js.Nullable.fromOption(onMouseOver),
        "onMouseOut": Js.Nullable.fromOption(onMouseOut),
        "onMouseUp": Js.Nullable.fromOption(onMouseUp),
        "onMouseDown": Js.Nullable.fromOption(onMouseDown),
        "onClick": Js.Nullable.fromOption(onClick),
      },
      children,
    );
};

[@bs.module] external circle : ReasonReact.reactClass = "react-art/Circle";

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
        ~onMouseMove: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseOver: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseOut: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseUp: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseDown: option(DomRe.MouseEvent.t => unit)=?,
        ~onClick: option(DomRe.MouseEvent.t => unit)=?,
        children,
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=circle,
      ~props={
        "radius": radius,
        "fill": fillToJs(fill),
        "stroke": Js.Nullable.fromOption(stroke),
        "strokeWidth": Js.Nullable.fromOption(strokeWidth),
        "strokeCap": Js.Nullable.fromOption(strokeCap),
        "strokeJoin": Js.Nullable.fromOption(strokeJoin),
        "strokeDash": Js.Nullable.fromOption(strokeDash),
        "scaleX": Js.Nullable.fromOption(scaleX),
        "scaleY": Js.Nullable.fromOption(scaleY),
        "scale": Js.Nullable.fromOption(scale),
        "x": Js.Nullable.fromOption(x),
        "y": Js.Nullable.fromOption(y),
        "originX": Js.Nullable.fromOption(originX),
        "originY": Js.Nullable.fromOption(originY),
        "transform": Js.Nullable.fromOption(transform),
        "cursor": Js.Nullable.fromOption(cursor),
        "opacity": Js.Nullable.fromOption(opacity),
        "visible": visible,
        "onMouseMove": Js.Nullable.fromOption(onMouseMove),
        "onMouseOver": Js.Nullable.fromOption(onMouseOver),
        "onMouseOut": Js.Nullable.fromOption(onMouseOut),
        "onMouseUp": Js.Nullable.fromOption(onMouseUp),
        "onMouseDown": Js.Nullable.fromOption(onMouseDown),
        "onClick": Js.Nullable.fromOption(onClick),
      },
      children,
    );
};

[@bs.module] external wedge : ReasonReact.reactClass = "react-art/Wedge";

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
        ~onMouseMove: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseOver: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseOut: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseUp: option(DomRe.MouseEvent.t => unit)=?,
        ~onMouseDown: option(DomRe.MouseEvent.t => unit)=?,
        ~onClick: option(DomRe.MouseEvent.t => unit)=?,
        children,
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=wedge,
      ~props={
        "outerRadius": outerRadius,
        "startAngle": startAngle,
        "endAngle": endAngle,
        "innerRadius": Js.Nullable.fromOption(innerRadius),
        "fill": fillToJs(fill),
        "stroke": Js.Nullable.fromOption(stroke),
        "strokeWidth": Js.Nullable.fromOption(strokeWidth),
        "strokeCap": Js.Nullable.fromOption(strokeCap),
        "strokeJoin": Js.Nullable.fromOption(strokeJoin),
        "strokeDash": Js.Nullable.fromOption(strokeDash),
        "scaleX": Js.Nullable.fromOption(scaleX),
        "scaleY": Js.Nullable.fromOption(scaleY),
        "scale": Js.Nullable.fromOption(scale),
        "x": Js.Nullable.fromOption(x),
        "y": Js.Nullable.fromOption(y),
        "originX": Js.Nullable.fromOption(originX),
        "originY": Js.Nullable.fromOption(originY),
        "transform": Js.Nullable.fromOption(transform),
        "cursor": Js.Nullable.fromOption(cursor),
        "opacity": Js.Nullable.fromOption(opacity),
        "visible": visible,
        "onMouseMove": Js.Nullable.fromOption(onMouseMove),
        "onMouseOver": Js.Nullable.fromOption(onMouseOver),
        "onMouseOut": Js.Nullable.fromOption(onMouseOut),
        "onMouseUp": Js.Nullable.fromOption(onMouseUp),
        "onMouseDown": Js.Nullable.fromOption(onMouseDown),
        "onClick": Js.Nullable.fromOption(onClick),
      },
      children,
    );
};
