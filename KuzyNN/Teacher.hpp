extern const int gradient_clip;

KuzyNN::teacher::Teacher::Teacher(const double& stepValue) : stepValue {stepValue} {}

KuzyNN::teacher::SGD::SGD(const double& stepValue, const KuzyMatrix::Matrix<double>& mat2teach) : Teacher(stepValue), param {&mat2teach}, buffer (mat2teach.get_shape()) {}

KuzyNN::teacher::SGD::SGD(const double& stepValue) : Teacher (stepValue) {}

void KuzyNN::teacher::SGD::update(const KuzyMatrix::Matrix<double>& paramWerror_vector) const {
    buffer = paramWerror_vector * stepValue;
    buffer.clip((static_cast<double>(gradient_clip)));
    param->subtract(buffer);
}

KuzyNN::teacher::SGD& KuzyNN::teacher::SGD::bind(const KuzyMatrix::Matrix<double>& mat2teach) const {
    return *(new KuzyNN::teacher::SGD (stepValue, mat2teach));
}

KuzyNN::teacher::Momentum::Momentum(const double& stepValue, const double& momentum) : Teacher {stepValue}, momentum {momentum} {}

KuzyNN::teacher::Momentum::Momentum(const double& stepValue, const double& momentum, const KuzyMatrix::Matrix<double>& param) : Teacher {stepValue}, momentum {momentum}, param {&param}, buffer_prev {param.get_shape()} {}


void KuzyNN::teacher::Momentum::update(const KuzyMatrix::Matrix<double>& paramWerror) const {
    buffer_prev = ((buffer_prev * momentum) + paramWerror) * stepValue;
    buffer_prev.clip(static_cast<double>(gradient_clip));
    param->subtract(buffer_prev);
}


KuzyNN::teacher::Momentum& KuzyNN::teacher::Momentum::bind(const KuzyMatrix::Matrix<double>& mat2teach) const {
    return *(new KuzyNN::teacher::Momentum (stepValue, momentum, mat2teach));
}

